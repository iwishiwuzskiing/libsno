#include <cmath>
#include <constants.h>
#include <sno/rotate.h>

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief rot_x Return the matrix to transforms a vector [x, y, z]
 * from one coordinate system to a coordinate system rotated about the x axis
 * by theta degrees
 * @param theta Rotation angle, degrees
 * @return Return the matrix for transormation to coordinate frame rotated by
 * theta degrees
 */
Eigen::Matrix3d so::Rotate::rot_x(double theta)
{
  Eigen::Matrix3d m;
  double rad = theta * DEG_TO_RAD;
  m << 1, 0, 0,
       0, std::cos(rad), std::sin(rad),
       0, -std::sin(rad), std::cos(rad);
  return m;
}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief rot_x Return the matrix to transforms a vector [x, y, z]
 * from one coordinate system to a coordinate system rotated about the y axis
 * by theta degrees
 * @param theta Rotation angle, degrees
 * @return Return the matrix for transormation to coordinate frame rotated by
 * theta degrees
 */
Eigen::Matrix3d so::Rotate::rot_y(double theta)
{
  Eigen::Matrix3d m;
  double rad = theta * DEG_TO_RAD;
  m << std::cos(rad), 0, -std::sin(rad),
      0, 1, 0,
      std::sin(rad), 0, std::cos(rad);
  return m;
}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief rot_x Return the matrix to transforms a vector [x, y, z]
 * from one coordinate system to a coordinate system rotated about the z axis
 * by theta degrees
 * @param theta Rotation angle, degrees
 * @return Return the matrix for transormation to coordinate frame rotated by
 * theta degrees
 */
Eigen::Matrix3d so::Rotate::rot_z(double theta)
{
  Eigen::Matrix3d m;
  double rad = theta * DEG_TO_RAD;
  m << std::cos(rad), std::sin(rad), 0,
      -std::sin(rad), std::cos(rad), 0,
      0, 0, 1;
  return m;
}


//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
