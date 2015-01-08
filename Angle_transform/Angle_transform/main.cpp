//#include "visualizer.h"
//#include "file_io.h"
//#include "utility.h"
//#include "bigScene_preSeg.h"
//
//const float PIOver2=1.570796;
//
//void quaternionToMatrix44(float x, float y, float z, float w, Eigen::Matrix4f& mat)
//{
//  mat = Eigen::Matrix4f::Identity();
//
//  mat(0,0) = (2. * (x*x + w*w) -1.);
//  mat(0,1) = (2. * (x*y - z*w));
//  mat(0,2) = (2. * (x*z + y*w));
//  mat(1,0) = (2. * (x*y + z*w));
//  mat(1,1) = (2. * (y*y + w*w)-1.);
//  mat(1,2) = (2. * (y*z - x*w));
//  mat(2,0) = (2. * (x*z - y*w));
//  mat(2,1) = (2. * (y*z + x*w));
//  mat(2,2) = (2. * (z*z + w*w)-1.);
//}
//
//void Matrix44ToQuaternion(Eigen::Matrix4f& matrix_transform, float *x, float *y, float *z, float *w)
//{
//  float w_squared=matrix_transform(0,0)+matrix_transform(1,1)+matrix_transform(2,2);
//  float x_squared=matrix_transform(0,0)-matrix_transform(1,1)-matrix_transform(2,2);
//  float y_squared=matrix_transform(1,1)+matrix_transform(0,0)+matrix_transform(2,2);
//  float z_squared=matrix_transform(2,2)+matrix_transform(0,0)+matrix_transform(1,1);
//
//  int max_index=0;
//
//  float max_squared=w_squared;
//
//  if(max_squared<x_squared){
//    max_squared=x_squared;
//    max_index=1;
//  }
//
//  if(max_squared<y_squared){
//    max_squared=y_squared;
//    max_index=2;
//  }
//
//  if(max_squared<z_squared){
//    max_squared=z_squared;
//    max_index=3;
//  }
//
//  float biggest_val=sqrt(max_squared+1.0f)*0.5f;
//  float mult=0.25f/biggest_val;
//
//  switch(max_index){
//  case 0:
//    *w=biggest_val;
//    *x=(matrix_transform(1,2)-matrix_transform(2,1))*mult;
//    *y=(matrix_transform(2,0)-matrix_transform(0,2))*mult;
//    *z=(matrix_transform(0,1)-matrix_transform(1,0))*mult;
//    break;
//  case 1:
//    *x=biggest_val;
//    *w=(matrix_transform(1,2)-matrix_transform(2,1))*mult;
//    *y=(matrix_transform(0,1)+matrix_transform(1,0))*mult;
//    *z=(matrix_transform(2,0)+matrix_transform(0,2))*mult;
//    break;
//  case 2:
//    *y=biggest_val;
//    *w=(matrix_transform(2,0)-matrix_transform(0,2))*mult;
//    *x=(matrix_transform(0,1)+matrix_transform(1,0))*mult;
//    *z=(matrix_transform(1,2)+matrix_transform(2,1))*mult;
//    break;
//  case 3:
//    *z=biggest_val;
//    *w=(matrix_transform(0,1)-matrix_transform(1,0))*mult;
//    *x=(matrix_transform(2,0)+matrix_transform(0,2))*mult;
//    *y=(matrix_transform(1,2)+matrix_transform(2,1))*mult;
//    break;
//  }
//}
//
//
//
//
//
//
//void GetEulerAngle(float x, float y, float z, float w, Eigen::Vector3f& angle)
//{
//  /*float test = y*z + x*w;
//  if (test > 0.4999f)
//  {
//  angle[2] = 2.0f * atan2(y, w);
//  angle[1] = PIOver2;
//  angle[0] = 0.0f;
//  return;
//  }
//  if (test < -0.4999f)
//  {
//  angle[2] = 2.0f * atan2(y, w);
//  angle[1] = -PIOver2;
//  angle[0] = 0.0f;
//  return;
//  }
//  float sqx = x * x;
//  float sqy = y * y;
//  float sqz = z * z;
//  angle[2] = atan2(2.0f * z * w - 2.0f * y * x, 1.0f - 2.0f * sqz - 2.0f * sqx);
//  angle[1] = asin(2.0f * test);
//  angle[0] = atan2(2.0f * y * w - 2.0f * z * x, 1.0f - 2.0f * sqy - 2.0f * sqx);*/
//
//  angle[0] = atan2(2.0f * x * w + 2.0f * y * z, 1.0f - 2.0f * x*x - 2.0f * y*y);
//  angle[1] = asin(2.0f * (w*y-z*x));
//  angle[2] = atan2(2.0f * z * w + 2.0f * y * x, 1.0f - 2.0f * y*y - 2.0f * z*z);
//
//}
//
//void CQuaternion(Eigen::Matrix4f& matrix_transform, float *x, float *y, float *z, float *w)
//{
//  float tr, s, q[4];
//  int i, j, k;
//
//  int nxt[3] = {1, 2, 0 };
//  // 计算矩阵轨迹
//  tr = matrix_transform(0,0) + matrix_transform(1,1) + matrix_transform(2,2);
//
//  // 检查矩阵轨迹是正还是负
//  if(tr>0.0f)
//  {
//    s = sqrt(tr + 1.0f);
//    *w = s / 2.0f;
//    s = 0.5f / s;
//    *x = (matrix_transform(1,2) - matrix_transform(2,1)) * s;
//    *y = (matrix_transform(2,0) - matrix_transform(0,2)) * s;
//    *z = (matrix_transform(0,1) - matrix_transform(1,0)) * s;
//  }
//  else
//  {
//    // 轨迹是负
//    // 寻找m11 m22 m33中的最大分量
//    i = 0;
//    if(matrix_transform(1,1)>matrix_transform(0,0)) i = 1;
//    if(matrix_transform(2,2)>matrix_transform(i,i)) i = 2;
//    j = nxt[i];
//    k = nxt[j];
//
//    s = sqrt((matrix_transform(i,i) - (matrix_transform(j,j) + matrix_transform(k,k))) + 1.0f);
//    q[i] = s * 0.5f;
//    if( s!= 0.0f) s = 0.5f / s;
//    q[3] = (matrix_transform(j,k) - matrix_transform(k,j)) * s;
//    q[j] = (matrix_transform(i,j) - matrix_transform(j,i)) * s;
//    q[k] = (matrix_transform(i,k) - matrix_transform(k,i)) * s;
//    *x = q[0];
//    *y = q[1];
//    *z = q[2];
//    *w = q[3];
//  }
//}
//
//
//void CQuaternion(const Eigen::Vector3f& angle, float *x, float *y, float *z, float *w)
//{
//  float cx = cos(angle[0]/2);
//  float sx = sin(angle[0]/2);
//  float cy = cos(angle[1]/2);
//  float sy = sin(angle[1]/2);
//  float cz = cos(angle[2]/2);
//  float sz = sin(angle[2]/2);
//
//  *w = cx*cy*cz + sx*sy*sz;
//  *x = sx*cy*cz - cx*sy*sz;
//  *y = cx*sy*cz + sx*cy*sz;
//  *z = cx*cy*sz - sx*sy*cz;
//}
//
//void GetMatrixRH(float x, float y, float z, float w, Eigen::Vector3f& translation, Eigen::Matrix4f& matrix_transform)
//{
//  float xx = x*x;
//  float yy = y*y;
//  float zz = z*z;
//  float xy = x*y;
//  float wz = -w*z;
//  float wy = -w*y;
//  float xz = x*z;
//  float yz = y*z;
//  float wx = -w*x;
//
//  matrix_transform(0,0) = 1.0f-2*(yy+zz);
//  matrix_transform(0,1) = 2*(xy-wz);
//  matrix_transform(0,2) = 2*(wy+xz);
//  matrix_transform(0,3) = translation[0];
//
//  matrix_transform(1,0) = 2*(xy+wz);
//  matrix_transform(1,1) = 1.0f-2*(xx+zz);
//  matrix_transform(1,2) = 2*(yz-wx);
//  matrix_transform(1,3) = translation[1];
//
//  matrix_transform(2,0) = 2*(xz-wy);
//  matrix_transform(2,1) = 2*(yz+wx);
//  matrix_transform(2,2) = 1.0f-2*(xx+yy);
//  matrix_transform(2,3) = translation[2];
//
//  matrix_transform(3,0) = 0;
//  matrix_transform(3,1) = 0;
//  matrix_transform(3,2) = 0;
//  matrix_transform(3,3) = 1.0f;
//
//
//
//  //float xx = x*x;
//  //float yy = y*y;
//  //float zz = z*z;
//  //float xy = x*y;
//  //float wz = w*z;
//  //float wy = w*y;
//  //float xz = x*z;
//  //float yz = y*z;
//  //float wx = w*x;
//
//  //matrix_transform(0,1) = 1.0f-2*(yy+zz);
//  //matrix_transform(0,2) = 2*(xy-wz);
//  //matrix_transform(0,3) = 2*(wy+xz);
//  //matrix_transform(0,4) = 0.0f;
//
//  //matrix_transform(1,1) = 2*(xy+wz);
//  //matrix_transform(1,2) = 1.0f-2*(xx+zz);
//  //matrix_transform(1,3) = 2*(yz-wx);
//  //matrix_transform(1,4) = 0.0f;
//
//  //matrix_transform(2,1) = 2*(xy-wy);
//  //matrix_transform(2,2) = 2*(yz+wx);
//  //matrix_transform(2,3) = 1.0f-2*(xx+yy);
//  //matrix_transform(2,3) = 0.0f;
//
//  //matrix_transform(3,1) = translation[0];
//  //matrix_transform(3,2) = translation[1];
//  //matrix_transform(3,3) = translation[2];
//  //matrix_transform(3,4) = 1.0f;
//}
//
//int main (int argc, char *argv[])
//{
//  Visualizer vs;
//  vs.viewer->removeAllPointClouds();
//  vs.viewer->removeCoordinateSystem();
//  vs.viewer->setBackgroundColor(0,0,0);
//
//  PointCloudPtr_RGB cloud(new PointCloud_RGB);
//  PointCloudPtr_RGB cloud2(new PointCloud_RGB);
//  NormalCloudTPtr normals(new NormalCloudT);
//
//  PointCloudPtr_RGB cloud_out(new PointCloud_RGB);
//
//  loadPointCloud_ply("data/calibration_data.ply", cloud);
//  loadPointCloud_ply("data/calibration_origin.ply", cloud2);
//
//  /* pcl::transformPointCloud(*cloud, *cloud_out, Eigen::Matrix<float, 3, 1>(0.542,0.063,1.001), Eigen::Quaternion<float>(0.527,0.513,0.535,0.417));
//
//  pcl::io::savePCDFileASCII ("data/cloud_out.pcd", *cloud_out);
//
//  vs.viewer->addPointCloud(cloud_out);*/
//
//
//
//  //vs.viewer->addPointCloud(cloud);
//
//  MyPointCloud_RGB plane_cloud1;
//  MyPointCloud rect_cloud1;
//  pcl::ModelCoefficients::Ptr plane_coefficients1(new pcl::ModelCoefficients);
//  PointCloudPtr_RGB remained_cloud1(new PointCloud_RGB);
//  big_plane_fitting(cloud, plane_cloud1, rect_cloud1, plane_coefficients1, remained_cloud1);
//
//  ////draw rect
//  //if(plane_cloud1.mypoints.size()>0)
//  //{
//  //  PointCloudPtr pc(new PointCloud);
//  //  MyPointCloud2PointCloud(rect_cloud1, pc);
//
//  //  std::stringstream st0;
//  //  std::stringstream st1;
//  //  std::stringstream st2;
//  //  std::stringstream st3;
//
//  //  st0<<"plane1_rect"<<"0";
//  //  st1<<"plane1_rect"<<"1";
//  //  st2<<"plane1_rect"<<"2";
//  //  st3<<"plane1_rect"<<"3";
//
//  //  std::string id_line0=st0.str();
//  //  std::string id_line1=st1.str();
//  //  std::string id_line2=st2.str();
//  //  std::string id_line3=st3.str();
//
//  //  vs.viewer->addLine(pc->at(0),pc->at(1),255,0,0,id_line0);
//  //  vs.viewer->addLine(pc->at(1),pc->at(2),255,0,0,id_line1);
//  //  vs.viewer->addLine(pc->at(2),pc->at(3),255,0,0,id_line2);
//  //  vs.viewer->addLine(pc->at(3),pc->at(0),255,0,0,id_line3);
//  //}
//
//  Eigen::Vector3d plane1_normal;
//  plane1_normal << plane_coefficients1->values[0], plane_coefficients1->values[1], plane_coefficients1->values[2];
//  plane1_normal.normalize();
//
//  double angle1=acos(plane1_normal.dot(Eigen::Vector3d(1,0,0)));
//  Eigen::Vector3d axis1 = plane1_normal.cross(Eigen::Vector3d(1,0,0));
//
//  Eigen::Matrix4d matrix1;
//  getRotationMatrix(axis1, angle1, matrix1);
//  Eigen::Matrix4f matrix_transform1 = matrix1.cast<float>();
//
//  //PointCloudPtr_RGB new_cloud(new PointCloud_RGB);
//  //pcl::transformPointCloud(*cloud, *new_cloud, matrix_transform1);
//  //pcl::copyPointCloud(*new_cloud, *cloud);
//
//  /*Eigen::Vector3d axis1=plane1_normal.cross(Eigen::Vector3d(0,0,1));
//  axis1.normalize();
//
//  Eigen::Matrix4d matrix1;
//  getRotationMatrix(axis1, angle1, matrix1);
//  Eigen::Matrix4f matrix_transform1 = matrix1.cast<float>();
//
//  getRotationMatrix(axis1, -angle1, matrix1);
//  Eigen::Matrix4f matrix_transform_r1 = matrix1.cast<float>();*/
//
//  //cout<<"plane1_normal:"<<endl<<plane1_normal<<endl;
//  //cout<<"angle1:"<<endl<<angle1<<endl;
//
//
//  MyPointCloud_RGB plane_cloud2;
//  MyPointCloud rect_cloud2;
//  pcl::ModelCoefficients::Ptr plane_coefficients2(new pcl::ModelCoefficients);
//  PointCloudPtr_RGB remained_cloud2(new PointCloud_RGB);
//  big_plane_fitting(remained_cloud1, plane_cloud2, rect_cloud2, plane_coefficients2, remained_cloud2);
//
//  ////draw rect
//  //if(plane_cloud2.mypoints.size()>0)
//  //{
//  //  PointCloudPtr pc(new PointCloud);
//  //  MyPointCloud2PointCloud(rect_cloud2, pc);
//
//  //  std::stringstream st0;
//  //  std::stringstream st1;
//  //  std::stringstream st2;
//  //  std::stringstream st3;
//
//  //  st0<<"plane2_rect"<<"0";
//  //  st1<<"plane2_rect"<<"1";
//  //  st2<<"plane2_rect"<<"2";
//  //  st3<<"plane2_rect"<<"3";
//
//  //  std::string id_line0=st0.str();
//  //  std::string id_line1=st1.str();
//  //  std::string id_line2=st2.str();
//  //  std::string id_line3=st3.str();
//
//  //  vs.viewer->addLine(pc->at(0),pc->at(1),0,255,0,id_line0);
//  //  vs.viewer->addLine(pc->at(1),pc->at(2),0,255,0,id_line1);
//  //  vs.viewer->addLine(pc->at(2),pc->at(3),0,255,0,id_line2);
//  //  vs.viewer->addLine(pc->at(3),pc->at(0),0,255,0,id_line3);
//  //}
//
//  Eigen::Vector3d plane2_normal;
//  plane2_normal << -plane_coefficients2->values[0], -plane_coefficients2->values[1], -plane_coefficients2->values[2];
//  plane2_normal.normalize();
//
//  double angle2=acos(plane2_normal.dot(Eigen::Vector3d(0,0,1)));
//  Eigen::Vector3d axis2 = plane2_normal.cross(Eigen::Vector3d(0,0,1));
//
//  Eigen::Matrix4d matrix2;
//  getRotationMatrix(axis2, angle2, matrix2);
//
//  Eigen::Matrix4f matrix_transform2 = matrix2.cast<float>();
//
//  PointCloudPtr_RGB new_cloud(new PointCloud_RGB);
// /* pcl::transformPointCloud(*cloud, *new_cloud, matrix_transform1);
//  pcl::copyPointCloud(*new_cloud, *cloud);
//  pcl::transformPointCloud(*cloud, *new_cloud, matrix_transform2);
//  pcl::copyPointCloud(*new_cloud, *cloud);*/
//  
//  Eigen::Matrix4d matrix3=matrix2*matrix1;
//  Eigen::Matrix4f matrix_transform3 = matrix3.cast<float>();
//  matrix_transform3(0, 3)+=0.676;
//  matrix_transform3(1, 3)+=0.0524;
//  matrix_transform3(2, 3)+=1.33;
//
//  pcl::transformPointCloud(*cloud2, *new_cloud, matrix_transform3);
//  pcl::copyPointCloud(*new_cloud, *cloud2);
//  
//  vs.viewer->addPointCloud(cloud2, "new_cloud");
//
//  //pcl::io::savePCDFileBinary("cloud.pcd", *cloud2);
//  Eigen::Matrix4f matrix_base_to_led;
//  Eigen::Vector3f translation(0.551, 0.079, 1.260);
//  GetMatrixRH(-0.044, 0.187, 0.024, 0.981, translation, matrix_base_to_led);
//
//  Eigen::Matrix4f matrix_base_to_led2;
//  quaternionToMatrix44(-0.044, 0.187, 0.024, 0.981, matrix_base_to_led2);
//
//  cout<<"matrix_base_to_led:\n"<<matrix_base_to_led<<endl;
//  cout<<"matrix_base_to_led2:\n"<<matrix_base_to_led2<<endl;
//
//
//  Eigen::Matrix4f matrix_base_to_led_inverse = matrix_base_to_led2.inverse();
//
//  matrix_transform3(0,3)=0;
//  matrix_transform3(1,3)=0;
//  matrix_transform3(2,3)=0;
//  matrix_transform3(3,3)=1.0f;
//
//  Eigen::Matrix4f matrix_base_to_kinect = matrix_transform3.inverse();
//  //Eigen::Matrix4f matrix_base_to_kinect_inverse = matrix_transform3.inverse();
//
//  
//
//
//  Eigen::Matrix4f matrix_led_to_kinect = matrix_base_to_led_inverse*matrix_base_to_kinect;
//  cout<<"matrix_base_to_led_inverse:\n"<<matrix_base_to_led_inverse<<endl;
//  cout<<"matrix_led_to_kinect:\n"<<matrix_led_to_kinect<<endl;
//
//  
//
//
//
//  float x;
//  float y;
//  float z;
//  float w;
//  //CQuaternion(Eigen::Vector3f(-0.083, 0.377, 0.033), &x, &y, &z, &w);
//  //cout<<"x:"<<x<<endl;
//  //cout<<"y:"<<y<<endl;
//  //cout<<"z:"<<z<<endl;
//  //cout<<"w:"<<w<<endl;
//
//
// /* CQuaternion(matrix_led_to_kinect, &x, &y, &z, &w);
//  cout<<"x:"<<x<<endl;
//  cout<<"y:"<<y<<endl;
//  cout<<"z:"<<z<<endl;
//  cout<<"w:"<<w<<endl;*/
//
//  //Matrix44ToQuaternion(matrix_led_to_kinect, &x, &y, &z, &w);
//  Matrix44ToQuaternion(matrix_base_to_kinect, &x, &y, &z, &w);
//  cout<<"x2:"<<x<<endl;
//  cout<<"y2:"<<y<<endl;
//  cout<<"z2:"<<z<<endl;
//  cout<<"w2:"<<w<<endl;
//
//  Eigen::Vector3f angle;
//  GetEulerAngle(x, y, z, w, angle);
//
//  cout<<"angle:"<<angle<<endl;
//
//  CQuaternion(Eigen::Vector3f(-0.083, 0.377, 0.033), &x, &y, &z, &w);
//  cout<<"x3:"<<x<<endl;
//  cout<<"y3:"<<y<<endl;
//  cout<<"z3:"<<z<<endl;
//  cout<<"w3:"<<w<<endl;
//
//  GetEulerAngle(x, y, z, w, angle);
//  cout<<"angle2:"<<angle<<endl;
//
//
//  /* Eigen::Matrix4f mat;
//  quaternionToMatrix44(x, y, z, w, mat);
//
//  cout<<"mat:\n"<<mat<<endl;*/
//
//  /*Eigen::Vector3f trans(matrix_led_to_kinect(0,3), matrix_led_to_kinect(1,3), matrix_led_to_kinect(2,3));
//  cout<<"trans:"<<trans<<endl;*/
//
//  /*Eigen::Vector3d axis3=plane3_normal.cross(Eigen::Vector3d(0,1,0));
//  axis3.normalize();
//
//  Eigen::Matrix4d matrix3;
//  getRotationMatrix(axis3, angle3, matrix3);
//  Eigen::Matrix4f matrix_transform3 = matrix3.cast<float>();
//
//  getRotationMatrix(axis3, -angle3, matrix3);
//  Eigen::Matrix4f matrix_transform_r3 = matrix3.cast<float>();*/
//
//  /*cout<<"plane2_normal:"<<endl<<plane2_normal<<endl;
//  cout<<"angle2:"<<endl<<angle2<<endl;
//
//  cout<<"plane2_normal.dot(plane1_normal):"<<plane2_normal.dot(plane1_normal)<<endl;
//
//
//  Eigen::Vector3d axis_x_new=plane1_normal.cross(plane2_normal);
//  axis_x_new.normalize();
//
//  axis_x_new=-axis_x_new;
//
//  double angle_x=acos(axis_x_new.dot(Eigen::Vector3d(0,1,0)));
//  cout<<"axis_x_new:"<<endl<<axis_x_new<<endl;
//  cout<<"angle_x:"<<endl<<angle_x<<endl;*/
//
//  
//
//  vs.show();
//
//  return 0;
//}
