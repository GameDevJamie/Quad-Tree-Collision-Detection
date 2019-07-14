#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

#include <vector>

namespace Genesis
{
	namespace math
	{
		class Transform
		{
			private:
				Matrix4x4 m_AbsoluteMatrix;	//The World Matrix (How the transform is defined in the world)
				Matrix4x4 m_RelativeMatrix;

				//Used for Mouse Rotation
				Vector2 m_CurrentMouse;	//The last known mouse position

			public:
				//CONSTRUCTOR: Initalise the Transform Data
				Transform
				(
					const Vector3& position = Vector3::kZero,
					const Quaternion& rotation = Quaternion::kIdentity,
					const Vector3& scale = Vector3::kOne
				);

				//COPY CONSTRUCTOR
				Transform(const Transform& trans);
				
				//DESTRUCTOR
				~Transform();


				//OPERATOR OVERLOADING
				//---------------------------------

				//Make this transform the same as the given transform
				Transform& operator=(const Transform& t)
				{
					m_AbsoluteMatrix = t.m_AbsoluteMatrix;
					m_RelativeMatrix = t.m_RelativeMatrix;

					return *this;
				}

				//---------------------------------


				//POSITION
				//------------------------------------

				inline Vector3 GetPosition() const
				{
					return m_RelativeMatrix.GetPosition();
					//if (!mp_Parent) return GetWorldPosition();
					//return m_RelativeMatrix.GetPosition();
				}

				inline Vector3 GetWorldPosition() const
				{
					return m_AbsoluteMatrix.GetPosition();
				}

				inline void SetPosition(const Vector3& position)
				{
					m_RelativeMatrix.SetPosition(position);
				}

				inline void SetPosition(const float& x, const float& y, const float& z)
				{
					m_RelativeMatrix.SetPositionX(x);
					m_RelativeMatrix.SetPositionY(y);
					m_RelativeMatrix.SetPositionZ(z);
				}

				//Translate/Move the node within the scene, on a given axis
				//@param axis: Which axis to move along
				//@param amount: How much to move the node
				//@param space: Move in World or Local Space
				void Translate(const float& amount, EAxis axis, ESpace space = ESpace::WORLD);

				//Translate/Move the node within the scene
				//@param amount: How much to move the node
				//@param space: Move in World or Local Space
				void Translate(const Vector3& amount, ESpace space = ESpace::WORLD);

				//------------------------------------


				//ROTATION
				//------------------------------------

				//Returns the Rotation of the Transform in Quaternions
				inline Quaternion GetRotation() const { return m_RelativeMatrix.GetRotation(); }

				//Set the New Rotation for the transform, using the given Quaternions
				inline void SetRotation(const Quaternion& q) { m_RelativeMatrix.SetRotation(q); }

				//Rotate the node on a given axis
				//@param axis: Which axis to rotate
				//@param amount: How much to rotate the node
				//@param space: Rotate using World or Local/Self Space
				void Rotate(const float& amount, EAxis axis, ESpace space = ESpace::WORLD);

				//Rotate the Transform (Rotates in the Order: Z, X, Y)
				//@param amount: How much to rotate
				//@param space: Rotate using World or Local/Self Space
				void Rotate(const Vector3& amount, ESpace space = ESpace::WORLD);

				//Rotate using the mouse
				//Compares the given mouse position with the last known mouse position to known when and how to rotate
				//Must be called per frame to work correctly
				//@param mousePos: The current mouse position
				//@param rotSpeed: How fast to rotate
				void MouseRotation(const Vector2& mousePos, const TFloat32& rotSpeed);

				//------------------------------------


				//SCALING
				//------------------------------------

				inline Vector3 GetScale() const { return m_RelativeMatrix.GetScale(); }

				void SetScale(const Vector3& scale)
				{
					m_RelativeMatrix.SetScale(scale);
				}
				void SetScale(const float& x, const float& y, const float& z)
				{
					m_RelativeMatrix.SetScaleX(x);
					m_RelativeMatrix.SetScaleY(y);
					m_RelativeMatrix.SetScaleZ(z);
				}

				//Scale the size of the node, on a given axis
				//@param axis: Which axis to scale the node
				//@param amount: How much to scale the node
				void Scale(const float& amount, EAxis axis);

				//Scale the size of the node
				//@param amount: How much to scale the node
				void Scale(const Vector3& amount);
				//------------------------------------


				//ACCESSORS
				//-------------------------------

				Matrix4x4 GetWorldMatrix() { return m_RelativeMatrix; }

				//-------------------------------



				//Attach this transform to another transform
				//If currently attached to a parent, will remove itself
				//@param parentTransform: The transform to attach to
				//Returns true on success
				//bool AttachTo(Transform* parentTransform)
				//{
				//	Detach();	//Detach from any parent currently attached to
				//
				//	mp_Parent = parentTransform;
				//
				//	//Set the ID of this transform, to be used when removing from the parent transform
				//	m_ID = mp_Parent->m_Counter;
				//	mp_Parent->m_Counter++;
				//
				//	parentTransform->m_Children.push_back(this);
				//
				//	return true;
				//}
				//
				////Detachs this Transform from the parent it is currently attached to
				////DOES NOT DE-ALLOCATE MEMORY
				//bool Detach()
				//{
				//	if (!mp_Parent) return true;
				//	
				//	//Find in parent's transform list and remove
				//	//----------------------
				//	for (auto it = mp_Parent->m_Children.begin(); it != mp_Parent->m_Children.end(); it++)
				//	{
				//		if ((*it)->m_ID == m_ID)
				//		{
				//			mp_Parent->m_Children.erase(it);
				//			break;
				//		}
				//	}
				//	//----------------------
				//
				//	mp_Parent = NULL;
				//
				//	return true;
				//}
		};
	}
}