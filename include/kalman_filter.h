/**
 * @class Kalman_filter
 * @brief Kalman filter implementation
 *
 * Assumes constant process noise (Q)
 *
 */

#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H
#include <stddef.h>
#include <eigen3/Eigen/Dense>
#include <functional>

template<int N>
class Kalman_filter
{
  typedef Eigen::Matrix<double, N, N> MatrixNN;
  typedef Eigen::Matrix<double, 1, N> Matrix1N;
  typedef Eigen::Matrix<double, N, 1> MatrixN1;

public:
  /**
   * @brief Constructor, a new Kalman filter.
   * @param A State transition matrix, NxN
   * @param B Control input model, NxN
   * @param Q Process noise covariance, NxN
   * @param x0 Initial system state, Nx1
   * @param P0 Initial error covariance, NxN
   */
  Kalman_filter(const MatrixNN& A,
                const MatrixNN& B,
                const MatrixNN& Q,
                const MatrixN1& x0,
                const MatrixNN& P0)
    :
      m_A(A),
      m_B(B),
      m_Q(Q),
      m_x(x0),
      m_P(P0)
  {

  }

  /**
   * @brief Predict the system state based on the current state
   */
  void Predict()
  {
    MatrixN1 u = MatrixN1::Zero();
    Predict(u);
  }

  /**
   * @brief Predict the system state based on the current state and the current
   * inputs, u
   * @param u Current inputs to the system, Nx1
   */
  void Predict(const MatrixN1& u)
  {
    m_x = m_A * m_x + m_B * u;
    m_P = m_A * m_P * m_A.transpose() + m_Q;
  }

  /**
   * @brief Update the current state estimate based on a single observation, z.
   * z = Hx + v, where x is the true system state, H is the mapping from true
   * state space to observed state space and v is observation error sampled
   * from a 0 mean normal distribution with covariance R. v~N(0,R)
   * @param z Observation, scalar
   * @param H Observation model, maps true state space to observed state space, 1xN
   * @param R Observation error covariance, scalar
   */
//  void Update(const double& z,
//              const Matrix1N& H,
//              const double& R)
//  {
//    Update(Eigen::Matrix<double, 1, 1>(z), H, R);
//  }

  /**
   * @brief Update the current state estimate based on a vector of observations,
   * z. z = Hx + v, where x is the true system state, H is the mapping from true
   * state space to observed state space and v is observation error sampled
   * from a 0 mean normal distribution with covariance R. v~N(0,R)
   * @param z Observation, Mx1
   * @param H Observation model, maps true state space to observed state space, MxN
   * @param R Observation error covariance, MxM
   */
  template<int M>
  void Update(const Eigen::Matrix<double, M, 1> z,
              const Eigen::Matrix<double, M, N>& H,
              const Eigen::Matrix<double, M, M>& R)
  {
    //Innovation
    Eigen::Matrix<double, 1, 1> y = z - H * m_x;

    //Innovation covariance
    Eigen::Matrix<double, 1, 1> S = H * m_P * H.transpose() + R;

    //Kalman gain
    MatrixN1 K = m_P * H.transpose() * S.inverse();

    //Update state estimate
    m_x = m_x + K * y;

    //Update error covariance
    m_P = (MatrixNN::Identity() - K*H) * m_P;
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

protected:
  /**
   * @brief m_A State transition matrix. Defines how the state changes based on
   * current state
   */
  MatrixNN m_A;

  /**
   * @brief m_B Control input matrix. Defines how the state changes based on
   * control inputs
   */
  MatrixNN m_B;

  /**
   * @brief m_Q Process noise covariance matrix
   */
  MatrixNN m_Q;

  /**
   * @brief x Current system state
   */
  MatrixN1 m_x;

  /**
   * @brief P Current estimate error covariance matrix
   */
  MatrixNN m_P;

private:

};

#endif
