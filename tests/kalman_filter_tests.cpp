#include <gtest/gtest.h>
#include <sno/kalman_filter.h>
#include <sno/time_utils.h>

namespace
{

// Call each function to ensure that they compile
TEST(KalmanTests, TestFunctionCompilation)
{
  const int N = 3;  // Number of states
  const int M = 2;  // Number of control inputs
  const int U = 4;  // Number of observations
  so::Kalman_filter<N,M>::MatrixNN NN =
      so::Kalman_filter<N,M>::MatrixNN::Identity();
  so::Kalman_filter<N,M>::MatrixN1 N1 =
      so::Kalman_filter<N,M>::MatrixN1::Identity();
  so::Kalman_filter<N,M>::MatrixNM NM =
      so::Kalman_filter<N,M>::MatrixNM::Identity();
  so::Kalman_filter<N,M>::MatrixM1 M1 =
      so::Kalman_filter<N,M>::MatrixM1::Identity();
  double t = so::Time_utils::Unix_time();

  so::Kalman_filter<N,M> k32(NN, NM, NN, N1, NN, t);
  k32.Predict(t);
  k32.Predict(M1, t);

  k32.Update(t, N1.transpose(), t);

  Eigen::Matrix<double, U, U> UU;
  Eigen::Matrix<double, U, 1> U1;
  Eigen::Matrix<double, U, N> UN;
  k32.Update(U1, UN, UU);
}

}
