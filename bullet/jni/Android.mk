LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
COLLISION_CollisionShapes = BulletCollision/CollisionShapes
COLLISION_Gimpact = BulletCollision/Gimpact
COLLISION_NarrowPhaseCollision = BulletCollision/NarrowPhaseCollision
LINEARMATH = LinearMath/btAlignedAllocator.cpp LinearMath/btConvexHull.cpp LinearMath/btConvexHullComputer.cpp LinearMath/btGeometryUtil.cpp LinearMath/btQuickprof.cpp LinearMath/btSerializer.cpp LinearMath/btVector3.cpp
DYNAMICS = BulletDynamics/Character/btKinematicCharacterController.cpp BulletDynamics/Vehicle/btRaycastVehicle.cpp BulletDynamics/Vehicle/btWheelInfo.cpp BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp BulletDynamics/Dynamics/btRigidBody.cpp BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp BulletDynamics/Dynamics/Bullet-C-API.cpp BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp BulletDynamics/ConstraintSolver/btContactConstraint.cpp BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp BulletDynamics/ConstraintSolver/btHingeConstraint.cpp BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp BulletDynamics/ConstraintSolver/btSliderConstraint.cpp BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp BulletDynamics/ConstraintSolver/btTypedConstraint.cpp BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp
COLLISION = BulletCollision/BroadphaseCollision/btAxisSweep3.cpp BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp BulletCollision/BroadphaseCollision/btDbvt.cpp BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp BulletCollision/BroadphaseCollision/btDispatcher.cpp BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp  \
	BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp BulletCollision/CollisionDispatch/btCollisionObject.cpp BulletCollision/CollisionDispatch/btCollisionWorld.cpp BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btGhostObject.cpp BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp BulletCollision/CollisionDispatch/btManifoldResult.cpp BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp BulletCollision/CollisionDispatch/btUnionFind.cpp BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp  \
	$(COLLISION_CollisionShapes)/btBox2dShape.cpp $(COLLISION_CollisionShapes)/btBoxShape.cpp $(COLLISION_CollisionShapes)/btBvhTriangleMeshShape.cpp $(COLLISION_CollisionShapes)/btCapsuleShape.cpp $(COLLISION_CollisionShapes)/btCollisionShape.cpp $(COLLISION_CollisionShapes)/btCompoundShape.cpp $(COLLISION_CollisionShapes)/btConcaveShape.cpp $(COLLISION_CollisionShapes)/btConeShape.cpp $(COLLISION_CollisionShapes)/btConvex2dShape.cpp $(COLLISION_CollisionShapes)/btConvexHullShape.cpp $(COLLISION_CollisionShapes)/btConvexInternalShape.cpp $(COLLISION_CollisionShapes)/btConvexPointCloudShape.cpp $(COLLISION_CollisionShapes)/btConvexPolyhedron.cpp $(COLLISION_CollisionShapes)/btConvexShape.cpp $(COLLISION_CollisionShapes)/btConvexTriangleMeshShape.cpp $(COLLISION_CollisionShapes)/btCylinderShape.cpp $(COLLISION_CollisionShapes)/btEmptyShape.cpp $(COLLISION_CollisionShapes)/btHeightfieldTerrainShape.cpp $(COLLISION_CollisionShapes)/btMinkowskiSumShape.cpp $(COLLISION_CollisionShapes)/btMultimaterialTriangleMeshShape.cpp $(COLLISION_CollisionShapes)/btMultiSphereShape.cpp $(COLLISION_CollisionShapes)/btOptimizedBvh.cpp $(COLLISION_CollisionShapes)/btPolyhedralConvexShape.cpp $(COLLISION_CollisionShapes)/btScaledBvhTriangleMeshShape.cpp $(COLLISION_CollisionShapes)/btShapeHull.cpp $(COLLISION_CollisionShapes)/btSphereShape.cpp $(COLLISION_CollisionShapes)/btStaticPlaneShape.cpp $(COLLISION_CollisionShapes)/btStridingMeshInterface.cpp $(COLLISION_CollisionShapes)/btTetrahedronShape.cpp $(COLLISION_CollisionShapes)/btTriangleBuffer.cpp $(COLLISION_CollisionShapes)/btTriangleCallback.cpp $(COLLISION_CollisionShapes)/btTriangleIndexVertexArray.cpp $(COLLISION_CollisionShapes)/btTriangleIndexVertexMaterialArray.cpp $(COLLISION_CollisionShapes)/btTriangleMesh.cpp $(COLLISION_CollisionShapes)/btTriangleMeshShape.cpp $(COLLISION_CollisionShapes)/btUniformScalingShape.cpp \
	$(COLLISION_Gimpact)/btContactProcessing.cpp $(COLLISION_Gimpact)/btGenericPoolAllocator.cpp $(COLLISION_Gimpact)/btGImpactBvh.cpp $(COLLISION_Gimpact)/btGImpactCollisionAlgorithm.cpp $(COLLISION_Gimpact)/btGImpactQuantizedBvh.cpp $(COLLISION_Gimpact)/btGImpactShape.cpp $(COLLISION_Gimpact)/btTriangleShapeEx.cpp $(COLLISION_Gimpact)/gim_box_set.cpp $(COLLISION_Gimpact)/gim_contact.cpp $(COLLISION_Gimpact)/gim_memory.cpp $(COLLISION_Gimpact)/gim_tri_collision.cpp  \
	$(COLLISION_NarrowPhaseCollision)/btContinuousConvexCollision.cpp $(COLLISION_NarrowPhaseCollision)/btConvexCast.cpp $(COLLISION_NarrowPhaseCollision)/btGjkConvexCast.cpp $(COLLISION_NarrowPhaseCollision)/btGjkEpa2.cpp $(COLLISION_NarrowPhaseCollision)/btGjkEpaPenetrationDepthSolver.cpp $(COLLISION_NarrowPhaseCollision)/btGjkPairDetector.cpp $(COLLISION_NarrowPhaseCollision)/btMinkowskiPenetrationDepthSolver.cpp $(COLLISION_NarrowPhaseCollision)/btPersistentManifold.cpp $(COLLISION_NarrowPhaseCollision)/btPolyhedralContactClipping.cpp $(COLLISION_NarrowPhaseCollision)/btRaycastCallback.cpp $(COLLISION_NarrowPhaseCollision)/btSubSimplexConvexCast.cpp $(COLLISION_NarrowPhaseCollision)/btVoronoiSimplexSolver.cpp
LOCAL_MODULE := bullet

LOCAL_ARM_MODE   := arm
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES := $(LINEARMATH) 

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/


LOCAL_LDLIBS += -L$(LOCAL_PATH)/libs 
LOCAL_LDLIBS += -ldl -llog -lgcc

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)