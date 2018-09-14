/**
 *
 */

#ifndef ROTATE_H
#define ROTATE_H

#include <eigen3/Eigen/Dense>

namespace Rotate
{
  /**
   * @brief Convert coordinates from body frame to earth frame given the current attitude of the vehicle
   * @param x X coordinate in body frame, will be populated with northing relative to vehicle
   * @param y Y coordinate in body frame, will be populated with easting relative to vehicle
   * @param z Z coordinate in body frame, will be populated with downing relative to vehicle
   * @param phi Roll angle, degrees
   * @param theta Pitch angle, degrees
   * @param psi, Heading, degrees
   */
  void body_2_earth(double& x,
                    double& y,
                    double& z,
                    const double phi,
                    const double theta,
                    const double psi);

  /**
   * @brief Convert coordinates from body frame to earth frame given the current attitude of the vehicle
   * @param position [X, Y, Z] coordinates in vehicle frame
   * @param attitude [roll, pitch, heading]
   * @return [X, Y, Z] coordinates in earth frame (northing, easting, downing)
   */
  Eigen::Vector3d body_2_earth(const Eigen::Vector3d& position,
                               const Eigen::Vector3d& attitude);

  /**
   * @brief Convert coordinates from earth frame
   * (northing/easting/downing relative to vehicle) to body fixed frame
   * @param position [Northing, easting, downing] relative to vehicle
   * @param attitude [roll, pitch, heading] of vehicle
   * @return [X, Y, Z] coordinates in body frame
   */
  Eigen::Vector3d earth_2_body(const Eigen::Vector3d& position,
                                      const Eigen::Vector3d& attitude);

  /**
   * @brief Return the matrix to transforms a vector [x, y, z]
   * from one coordinate system to a coordinate system rotated about the x axis
   * by theta degrees
   * @param theta Rotation angle, degrees
   * @return Return the matrix for transormation to coordinate frame rotated by
   * theta degrees
   */
  Eigen::Matrix3d rot_x(double theta);

  /**
   * @brief Return the matrix to transforms a vector [x, y, z]
   * from one coordinate system to a coordinate system rotated about the y axis
   * by theta degrees
   * @param theta Rotation angle, degrees
   * @return Return the matrix for transormation to coordinate frame rotated by
   * theta degrees
   */
  Eigen::Matrix3d rot_y(double theta);

  /**
   * @brief Return the matrix to transforms a vector [x, y, z]
   * from one coordinate system to a coordinate system rotated about the z axis
   * by theta degrees
   * @param theta Rotation angle, degrees
   * @return Return the matrix for transormation to coordinate frame rotated by
   * theta degrees
   */
  Eigen::Matrix3d rot_z(double theta);

}

#endif
