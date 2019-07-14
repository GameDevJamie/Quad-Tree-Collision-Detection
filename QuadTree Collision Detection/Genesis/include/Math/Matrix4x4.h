#pragma once

/************************************************************
FILE: Matrix4x4.h

SUMMARY: A 4x4 Matrix. 
		Contains Math for various Matrix calculations and for constructing matrices (Translation, Scale and Rotation)

		This Matrix Class uses the below form for matrix calculations:
		Xx Xy Xz 0	(X Axis)
		Yx Yy Yz 0	(Y Axis)
		Zx Zy Zz 0	(Z Axis)
		Px Py Pz 1	(Position)
************************************************************/

#include "Vector3.h"
#include "Vector4.h"

namespace Genesis
{
	namespace math
	{
		//Forward Declarations
		class Quaternion;


		enum class ESpace
		{
			WORLD,
			LOCAL
		};

		enum class EAxis
		{
			X,
			Y,
			Z
		};


		class Matrix4x4
		{
			public:
				//Matrix Elements
				TFloat32 m00, m01, m02, m03;
				TFloat32 m10, m11, m12, m13;
				TFloat32 m20, m21, m22, m23;
				TFloat32 m30, m31, m32, m33;

			public:
				//Standard Matrices
				static const Matrix4x4 kIdentity;

				//CONSTRUCTORS/DESTRUCTORS
				//----------------------------------

				//Will construct the matrix as an Identity Matrix
				Matrix4x4();

				//Construct the matrix using the given position, rotation and scale values (World Matrix)
				//Rotations in Quaternions
				Matrix4x4
				(
					const Vector3& position,
					const Quaternion& rotation,
					const Vector3& scale = Vector3::kOne
				);
				
				//Copy Constructor
				Matrix4x4(const Matrix4x4& m);

				//----------------------------------


				//OPERATOR OVERLOADING
				//----------------------------------

				Matrix4x4& operator=(const Matrix4x4& m)
				{
					if (this != &m)
					{
						m00 = m.m00;
						m01 = m.m01;
						m02 = m.m02;
						m03 = m.m03;
								
						m10 = m.m10;
						m11 = m.m11;
						m12 = m.m12;
						m13 = m.m13;
							
						m20 = m.m20;
						m21 = m.m21;
						m22 = m.m22;
						m23 = m.m23;
							
						m30 = m.m30;
						m31 = m.m31;
						m32 = m.m32;
						m33 = m.m33;
					}
					return *this;
				}

				friend inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
				{
					Matrix4x4 result;

					result.m00 = m1.m00*m2.m00 + m1.m01*m2.m10 + m1.m02*m2.m20 + m1.m03*m2.m30;
					result.m01 = m1.m00*m2.m01 + m1.m01*m2.m11 + m1.m02*m2.m21 + m1.m03*m2.m31;
					result.m02 = m1.m00*m2.m02 + m1.m01*m2.m12 + m1.m02*m2.m22 + m1.m03*m2.m32;
					result.m03 = m1.m00*m2.m03 + m1.m01*m2.m13 + m1.m02*m2.m23 + m1.m03*m2.m33;
						 		  		 		  	 
					result.m10 = m1.m10*m2.m00 + m1.m11*m2.m10 + m1.m12*m2.m20 + m1.m13*m2.m30;
					result.m11 = m1.m10*m2.m01 + m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31;
					result.m12 = m1.m10*m2.m02 + m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32;
					result.m13 = m1.m10*m2.m03 + m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33;
						 		  		 		  
					result.m20 = m1.m20*m2.m00 + m1.m21*m2.m10 + m1.m22*m2.m20 + m1.m23*m2.m30;
					result.m21 = m1.m20*m2.m01 + m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31;
					result.m22 = m1.m20*m2.m02 + m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32;
					result.m23 = m1.m20*m2.m03 + m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33;
						 		  		 		 
					result.m30 = m1.m30*m2.m00 + m1.m31*m2.m10 + m1.m32*m2.m20 + m1.m33*m2.m30;
					result.m31 = m1.m30*m2.m01 + m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31;
					result.m32 = m1.m30*m2.m02 + m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32;
					result.m33 = m1.m30*m2.m03 + m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33;

					return result;
				}

				inline Vector4& operator[](const TInt32 row)
				{
					
				}

				//----------------------------------


				//Decompose the matrix into its basic elements (Position, Rotation, and Scale)
				//Pass NULL to ignore certain elements
				void Decompose
				(
					Vector3* position,
					Quaternion* rotation,
					Vector3* scale
				) const;



				//FUNCTIONS FOR SETTING THIS MATRIX
				//-----------------------------------

				//Turn this matrix into the Identity matrix
				void MakeIdentity();

				//Turn this matrix into a Translation Matrix
				//@param translation: The position vector
				void MakeTranslation(const Vector3& translation);

				//Turn this matrix into a full Rotation Matrix (X Y Z)
				//@param rotation: The rotation in Quaternions
				void MakeRotation(const Quaternion& rotation);

				//Set this matrix to a scaling matrix. Sets all values the same
				//@param scale: The scale value for all Axis
				void MakeScaling(const TFloat32& scale);

				//Set this matrix to a scaling matrix
				//@param scale: The different scale values
				void MakeScaling(const Vector3& scale);

				//Set this matrix to a world matrix using the given position, rotation and scale vectors
				//@param position: The position vector
				//@param rotation: The rotation in Quaternions
				//@param scale: The scale values
				void MakeWorld(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

				//Set this matrix to its Inverse (Multiplying the Inverse by the original equals the Identity matrix)
				void Invert();

				//Multiply this matrix with the given matrix
				void Multiply(const Matrix4x4&);

				//Set all matrix elements at once
				void SetAll
				(
					const TFloat32& f00, const TFloat32& f01, const TFloat32& f02, const TFloat32& f03,
					const TFloat32& f10, const TFloat32& f11, const TFloat32& f12, const TFloat32& f13,
					const TFloat32& f20, const TFloat32& f21, const TFloat32& f22, const TFloat32& f23,
					const TFloat32& f30, const TFloat32& f31, const TFloat32& f32, const TFloat32& f33
				);

				//Tranpose this matrix (Rows become Columns and vice versa)
				void Transpose();				

				//-----------------------------------


				//Transformation Functions (Position, Rotation and Scale)
				//----------------------------------

				//TRANSLATION
				void TranslateX(const TFloat32& x, ESpace space = ESpace::WORLD, bool withScaling = false);
				void TranslateY(const TFloat32& y, ESpace space = ESpace::WORLD, bool withScaling = false);
				void TranslateZ(const TFloat32& z, ESpace space = ESpace::WORLD, bool withScaling = false);

				void SetPosition(const Vector3& newPos);
				void SetPositionX(const TFloat32& xPos);
				void SetPositionY(const TFloat32& yPos);
				void SetPositionZ(const TFloat32& zPos);

				Vector3 GetPosition() const;
				TFloat32 GetPositionX() const;
				TFloat32 GetPositionY() const;
				TFloat32 GetPositionZ() const;


				//ROTATION
				void RotateX(const TFloat32& radians, ESpace space = ESpace::WORLD);
				void RotateY(const TFloat32& radians, ESpace space = ESpace::WORLD);
				void RotateZ(const TFloat32& radians, ESpace space = ESpace::WORLD);

				void SetRotation(const Quaternion& newRotation);
				Quaternion GetRotation() const;


				//SCALE
				void ScaleX(const TFloat32& xScale);
				void ScaleY(const TFloat32& yScale);
				void ScaleZ(const TFloat32& zScale);

				void SetScale(const Vector3& newScale);
				void SetScaleX(const TFloat32& xScale);
				void SetScaleY(const TFloat32& yScale);
				void SetScaleZ(const TFloat32& zScale);

				Vector3 GetScale() const;


				//----------------------------------


				//Vector Multiplication
				//-----------------------------------

				//Returns a vector transformed by this matrix and the given vector (V*M)
				Vector4 Transform(const Vector4& v) const;

				//-----------------------------------

				Vector4 GetRow(const TInt32& row)
				{
					if (row < 0 || row >= 4) return Vector4::kZero;

					switch (row)
					{
						case 0:
							return Vector4(m00, m01, m02, m03);
							break;

						case 1:
							return Vector4(m10, m11, m12, m13);
							break;

						case 2:
							return Vector4(m20, m21, m22, m23);
							break;

						case 3:
							return Vector4(m30, m31, m32, m33);
							break;
					}
					return Vector4::kZero;
				}
				Vector4 GetCol(const TInt32& col)
				{
					if (col < 0 || col >= 4) return Vector4::kZero;

					switch (col)
					{
						case 0:
							return Vector4(m00, m10, m20, m30);
							break;

						case 1:
							return Vector4(m01, m11, m21, m31);
							break;

						case 2:
							return Vector4(m02, m12, m22, m32);
							break;

						case 3:
							return Vector4(m03, m13, m23, m33);
							break;
					}
					return Vector4::kZero;
				}

				void SetRow(const TInt32& row, const Vector4& values)
				{
					if (row < 0 || row >= 4) return;

					switch (row)
					{
						case 0:
							m00 = values.x;
							m01 = values.y;
							m02 = values.z;
							m03 = values.w;
							break;

						case 1:
							m10 = values.x;
							m11 = values.y;
							m12 = values.z;
							m13 = values.w;
							break;

						case 2:
							m20 = values.x;
							m21 = values.y;
							m22 = values.z;
							m23 = values.w;
							break;

						case 3:
							m30 = values.x;
							m31 = values.y;
							m32 = values.z;
							m33 = values.w;
							break;
					}
				}
				void SetCol(const TInt32& col, const Vector4& values)
				{
					if (col < 0 || col >= 4) return;

					switch (col)
					{
						case 0:
							m00 = values.x;
							m10 = values.y;
							m20 = values.z;
							m30 = values.w;
							break;

						case 1:
							m01 = values.x;
							m11 = values.y;
							m21 = values.z;
							m31 = values.w;
							break;

						case 2:
							m02 = values.x;
							m12 = values.y;
							m22 = values.z;
							m32 = values.w;
							break;

						case 3:
							m03 = values.x;
							m13 = values.y;
							m23 = values.z;
							m33 = values.w;
							break;
						}
				}
		};

		//NON-MEMBER MATRIX FUNCTIONS
		//----------------------------

		Matrix4x4 Matrix4x4Identity();
		Matrix4x4 Matrix4x4Translation(const Vector3& pos);
		Matrix4x4 Matrix4x4Rotation(const Quaternion& rotation);
		Matrix4x4 Matrix4x4Scaling(const TFloat32& scale);
		Matrix4x4 Matrix4x4Inverse(const Matrix4x4& m);

		//----------------------------
	}
}