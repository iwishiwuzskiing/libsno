/**
 * @class Kalman_filter
 * @brief Kalman filter implementation
 *
 * Assumes constant process noise (Q)
 *
 */

#ifndef SO_KALMAN_FILTER_H
#define SO_KALMAN_FILTER_H
#include <stddef.h>
#include <functional>
#include <bitset>
#include <type_traits>
#include <eigen3/Eigen/Dense>

namespace so
{

template<int N, int M = N>
class Kalman_filter
{
public:
  typedef Eigen::Matrix<double, N, N> MatrixNN;
  typedef Eigen::Matrix<double, 1, N> Matrix1N;
  typedef Eigen::Matrix<double, N, 1> MatrixN1;
  typedef Eigen::Matrix<double, N, M> MatrixNM;
  typedef Eigen::Matrix<double, M, 1> MatrixM1;

public:
  /**
   * @brief Constructor, a new Kalman filter.
   * @param A Function that calculates the state transition matrix (NxN)
   * @param B Function that calculates the control input model (NxM)
   * @param Q  Function that calculates the process noise covariance (NxN)
   * @param x0 Initial system state, Nx1
   * @param P0 Initial error covariance, NxN
   * @param t0 Initial timestamp
   */
  template<class S, class T>
  Kalman_filter(S* model,
                MatrixNN(S::*A)(const double),
                MatrixNM(S::*B)(const double),
                MatrixNN(S::*Q)(const double),
                const MatrixN1& x0,
                const MatrixNN& P0,
                const std::bitset<N> polar_correct = false,
                typename std::enable_if<std::is_base_of<T,S>::value>::type* = nullptr)
    :
      m_A([model, A](const double t)->MatrixNN {return model->A(t);}),
      m_B([model, B](const double t)->MatrixNM {return model->B(t);}),
      m_Q([model, Q](const double t)->MatrixNN {return model->Q(t);}),
      m_x(x0),
      m_P(P0),
      m_polar_correct(polar_correct)
  {
  }

  /**
   * @brief Constructor, a new Kalman filter.
   * @param A Function that calculates the state transition matrix (NxN)
   * @param B Function that calculates the control input model (NxM)
   * @param Q  Function that calculates the process noise covariance (NxN)
   * @param x0 Initial system state, Nx1
   * @param P0 Initial error covariance, NxN
   * @param t0 Initial timestamp
   */
  Kalman_filter(MatrixNN(*A)(const double),
                MatrixNM(*B)(const double),
                MatrixNN(*Q)(const double),
                const MatrixN1& x0,
                const MatrixNN& P0,
                const std::bitset<N> polar_correct = false)
    :
      m_A(A),
      m_B(B),
      m_Q(Q),
      m_x(x0),
      m_P(P0),
      m_polar_correct(polar_correct)
  {
  }

  /**
   * @brief Constructor, a new Kalman filter.
   * @param A State transition matrix, NxN
   * @param B Control input model, NxN      //TODO: NxM?
   * @param Q Process noise covariance, NxN
   * @param x0 Initial system state, Nx1
   * @param P0 Initial error covariance, NxN
   * @param t0 Initial timestamp
   */
  Kalman_filter(const MatrixNN& A,
                const MatrixNM& B,
                const MatrixNN& Q,
                const MatrixN1& x0,
                const MatrixNN& P0,
                const std::bitset<N> polar_correct = false)
    :
      m_A([A](const double){return A;}),
      m_B([B](const double){return B;}),
      m_Q([Q](const double){return Q;}),
      m_x(x0),
      m_P(P0),
      m_polar_correct(polar_correct)
  {
  }

  /**
   * @brief Predict the system state based on the current state
   * @param Current timestamp
   */
  void Predict(const double t)
  {
    MatrixM1 u = MatrixM1::Zero();
    Predict(u, t);
  }

  /**
   * @brief Predict the system state based on the current state and the current
   * inputs, u
   * @param u Current inputs to the system, Mx1
   * @param t Current timestamp
   */
  void Predict(const MatrixM1& u, const double t)
  {
    MatrixNN A = m_A(t);
    MatrixNM B = m_B(t);
    MatrixNN Q = m_Q(t);
    m_x = A * m_x + B * u;
    m_P = A * m_P * A.transpose() + Q;
  }

  /**
   * @brief Update the current state estimate based on a single observation, z.
   * z = Hx + v, where x is the true system state, H is the mapping from true
   * state space to observed state space and v is observation error sampled
   * from a 0 mean normal distribution with covariance R. v~N(0,R). Predict()
   * function should be called to propagate the estimated solution up to the
   * current timestamp before update.
   * @param z Observation, scalar
   * @param H Observation model, maps true state space to observed state space, 1xN
   * @param R Observation error covariance, scalar
   */
  void Update(const double z,
              const Matrix1N& H,
              const double R)
  {
    Update(Eigen::Matrix<double, 1, 1>(z),
           H,
           Eigen::Matrix<double, 1, 1>(R));
  }

  /**
   * @brief Update the current state estimate based on a vector of observations,
   * z. z = Hx + v, where x is the true system state, H is the mapping from true
   * state space to observed state space and v is observation error sampled
   * from a 0 mean normal distribution with covariance R. v~N(0,R). Predict()
   * function should be called to propagate the estimated solution up to the
   * current timestamp before update.
   * @param z Observation, Ux1
   * @param H Observation model, maps observation state space into filter state
   * space, UxN
   * @param R Observation error covariance, UxU
   */
  template<int U>
  void Update(const Eigen::Matrix<double, U, 1> z,
              const Eigen::Matrix<double, U, N>& H,
              const Eigen::Matrix<double, U, U>& R)
  {
    // Innovation
    Eigen::Matrix<double, U, 1> y = z - H * m_x;

    // Polar corret
    if(m_polar_correct.any())
    {

      for(int r = 0; r < y.rows(); r++)
      {
        if(m_polar_correct[r])
        {
          //FIXME: polar correction function
          // Degrees
          if( std::fabs(y(r)) > 180.0)
          {
            y(r) = ( (-y(r)/std::fabs(y(r)) ) * 360.0) + y(r);
          }
        }
      }
    }

    // Innovation covariance
    Eigen::Matrix<double, U, U> S = H * m_P * H.transpose() + R;

    // Optimal Kalman gain
    const Eigen::Matrix<double, N, U> K = m_P * H.transpose() * S.inverse();



    // Update state estimate
    m_x = m_x + K * y;

    // Update error covariance
    m_P = (MatrixNN::Identity() - K*H) * m_P;

    // Joseph form of error covariance, valid for any Kalman gain
//    m_P = (MatrixNN::Identity() - K*H) * m_P *
//          (MatrixNN::Identity() - K*H).eval().transpose() +
//          K * R * K.transpose();

    //TODO: update last timestamp here?
  }

  /**
   * @brief Get the current state estimate (x)
   * @return Current state estimate
   */
  MatrixN1 Get_state_estimate() const {return m_x;}

  /**
   * @brief Get the current error covariance (P)
   * @return Current error covariance
   */
  MatrixNN Get_error_covariance() const {return m_P;}

  void Set_state_estimate(const MatrixNN& x)
  {
    //TODO: update time
    m_x = x;
  }

  void Set_error_covariance(const MatrixNN& p)
  {
    m_P = p;
  }

private:
  /**
   * @brief Function that takes time as an input and returns the state
   * transition matrix for the given time
   * @return State transition (A) matrix for the given time
   */
  std::function<MatrixNN (const double)> m_A;

  /**
   * @brief Function that takes time as an input and returns the control input
   * matrix for the given time
   * @return Control input (B) matrix for the given time
   */
  std::function<MatrixNM (const double)> m_B;

  /**
   * @brief Function that takes time as an input and returns the process
   * noise covariance matrix matrix for the given time
   */
  std::function<MatrixNM (const double)> m_Q;

  /**
   * @brief Current system state
   */
  MatrixN1 m_x;

  /**
   * @brief Current estimate error covariance matrix
   */
  MatrixNN m_P;

  /**
   * @brief True if values should be polar corrected
   */
  std::bitset<N> m_polar_correct;

};
} //namespace so

#endif
