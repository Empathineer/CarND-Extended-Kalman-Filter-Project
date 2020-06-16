#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_
#include "tools.h"

#include "Eigen/Dense"

class KalmanFilter {
 public:
  /**
   * Constructor
   */
  KalmanFilter();

  /**
   * Destructor
   */
  virtual ~KalmanFilter();

  /**
   * Init Initializes Kalman filter
   * @param x_in Initial state
   * @param P_in Initial state covariance
   * @param F_in Transition matrix
   * @param H_in Measurement matrix
   * @param R_in Measurement covariance matrix
   * @param Q_in Process covariance matrix
   */
  void Init(Eigen::VectorXd &x_in, Eigen::MatrixXd &P_in, Eigen::MatrixXd &F_in,
            Eigen::MatrixXd &H_in, Eigen::MatrixXd &R_in, Eigen::MatrixXd &Q_in);

   
  
  //Accessors 
  Eigen::VectorXd getx_();
  
  //Mutators 
  void setx_(const Eigen::VectorXd x);
  void setF_(float dt);
  void setQ_(float dt, float noise_ax, float noise_ay);
  void initP_(float variance);

  /**
   * Prediction Predicts the state and the state covariance
   * using the process model
   * @param delta_T Time between k and k+1 in s
   */
  void Predict();

  /**
   * Updates the state by using standard Kalman Filter equations
   * @param z The measurement at k+1
   */
  void Update(const Eigen::VectorXd &z, const Eigen::MatrixXd &R, const Eigen::MatrixXd &H);

  /**
   * Updates the state by using Extended Kalman Filter equations
   * @param z The measurement at k+1
   */
  void UpdateEKF(const Eigen::VectorXd &z, const Eigen::MatrixXd &R, const Eigen::MatrixXd &Hj);

  // state vector
  Eigen::VectorXd x_;

  // state covariance matrix
  Eigen::MatrixXd P_;

  // state transition matrix
  Eigen::MatrixXd F_;

  // process covariance matrix
  Eigen::MatrixXd Q_;

  // measurement matrix
  Eigen::MatrixXd H_;

  // measurement covariance matrix
  Eigen::MatrixXd R_;
  
  
  void ApplyKF(const Eigen::VectorXd &z, const Eigen::VectorXd &z_pred);
  
 private:
  //tool object used for converting polar to cartesion and vice versa 
 	Tools tools;
  
};

#endif // KALMAN_FILTER_H_
