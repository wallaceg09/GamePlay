/*
 * Camera.h
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Ref.h"
#include "Transform.h"
#include "Frustum.h"
#include "Viewport.h"

namespace gameplay
{

class Node;

/**
 * Defines a view of a scene.
 */
class Camera : public Ref, public Transform::Listener
{
    friend class Node;

public:

    /**
     * The type of camera.
     */
    enum Type
    {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2
    };

    /**
     * Creates a perspective camera.
     *
     * @param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).
     * @param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
     * @param nearPlane The near plane distance.
     * @param farPlane The far plane distance.
     */
    static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

    /**
     * Creates an orthographic camera.
     *
     * @param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
     * @param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
     * @param aspectRatio The aspect ratio of the orthographic projection.
     * @param nearPlane The near plane distance.
     * @param farPlane The far plane distance.
     */
    static Camera* createOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane);

    /**
     * Gets the type of camera.
     *
     * @return The camera type.
     */
    Camera::Type getCameraType() const;

    /**
     * Gets the field of view for a perspective camera.
     *
     * @return The field of view.
     */
    float getFieldOfView() const;

    /**
     * Sets the field of view.
     *
     * @param fieldOfView The field of view.
     */
    void setFieldOfView(float fieldOfView);

    /**
     * Gets the x-zoom (magnification) for an orthographic camera.
     * Default is 1.0f.
     *
     * @return The magnification (zoom) for x.
     */
    float getZoomX() const;

    /**
     * Sets the x-zoom (magnification) for a orthographic camera.
     * Default is 1.0f.
     *
     * @param zoomX The magnification (zoom) for x.
     */
    void setZoomX(float zoomX);

    /**
     * Gets the y-zoom (magnification) for a orthographic camera.
     * Default is 1.0f.
     *
     * @return The magnification (zoom) for y.
     */
    float getZoomY() const;

    /**
     * Sets the y-zoom (magnification) for a orthographic camera.
     *
     * @param zoomY The magnification (zoom) for y.
     */
    void setZoomY(float zoomY);

    /**
     * Gets the aspect ratio.
     *
     * @return The aspect ratio.
     */
    float getAspectRatio() const;

    /**
     * Sets the aspect ratio.
     *
     * @param aspectRatio The aspect ratio.
     */
    void setAspectRatio(float aspectRatio);

    /**
     * Gets the near z clipping plane distance.
     *
     * @return The near z clipping plane distance.
     */
    float getNearPlane() const;

    /**
     * Sets the near z clipping plane distance.
     *
     * @param nearPlane The near z clipping plane distance.
     */
    void setNearPlane(float nearPlane);

    /**
     * Gets the far z clipping plane distance.
     *
     * @return The far z clipping plane distance.
     */
    float getFarPlane() const;

    /**
     * Sets the far z clipping plane distance.
     *
     * @param farPlane The far z clipping plane distance.
     */
    void setFarPlane(float farPlane);

    /**
     * Gets the node that this camera is attached to.
     *
     * @return The node that this camera is attached to.
     */
    Node* getNode() const;

    /**
     * Gets the camera's view matrix.
     *
     * @return The camera view matrix.
     */
    const Matrix& getViewMatrix() const;

    /**
     * Gets the camera's inverse view matrix.
     *
     * @return The camera inverse view matrix.
     */
    const Matrix& getInverseViewMatrix() const;

    /**
     * Gets the camera's projection matrix.
     *
     * @return The camera projection matrix.
     */
    const Matrix& getProjectionMatrix() const;

    /**
     * Gets the camera's view * projection matrix.
     *
     * @return The camera view * projection matrix.
     */
    const Matrix& getViewProjectionMatrix() const;

    /**
     * Gets the camera's inverse view * projection matrix.
     *
     * @return The camera inverse view * projection matrix.
     */
    const Matrix& getInverseViewProjectionMatrix() const;

    /**
     * Gets the view bounding frustum.
     *
     * @return The viewing bounding frustum.
     */
    const Frustum& getFrustum() const;

    /**
     * Projects the specified world position into the viewport coordinates.
     *
     * @param viewport The viewport to use, or NULL to use a viewport the size of the window.
     * @param position The world space position.
     * @param x The returned viewport x coordinate.
     * @param y The returned viewport y coordinate.
     * @param depth The returned pixel depth (can be NULL).
     */
    void project(const Viewport* viewport, const Vector3& position, float* x, float* y, float* depth = NULL);

    /**
     * Converts a viewport-space coordinate to a world-space position for the given depth value.
     *
     * The depth parameter is a value ranging between 0 and 1, where 0 returns a point on the
     * near clipping plane and 1 returns a point on the far clipping plane.
     *
     * @param viewport The viewport to use, or NULL to use a viewport the size of the window.
     * @param x The viewport-space x coordinate.
     * @param y The viewport-space y coordinate.
     * @param depth The depth range.
     * @param dst The world space position.
     */
    void unproject(const Viewport* viewport, float x, float y, float depth, Vector3* dst);

    /**
     * Picks a ray that can be used for picking given the specified viewport-space coordinates.
     *
     * @param viewport The viewport to use, or NULL to use a viewport the size of the window.
     * @param x The viewport x-coordinate.
     * @param y The viewport y-coordinate.
     * @param dst The computed pick ray.
     */
    void pickRay(const Viewport* viewport, float x, float y, Ray* dst);

private:

    /**
     * Constructor.
     */
    Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

    /**
     * Constructor.
     */
    Camera(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane);

    /**
     * Destructor.
     */
    virtual ~Camera();

    /**
     * @see Transform::Listener::transformChanged
     */
    void transformChanged(Transform* transform);

    /**
     * Sets the node associated with this camera.
     */
    void setNode(Node* node);

    Camera::Type _type;
    float _fieldOfView;
    float _zoom[2];
    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    mutable Matrix _view;
    mutable Matrix _projection;
    mutable Matrix _viewProjection;
    mutable Matrix _inverseView;
    mutable Matrix _inverseViewProjection;
    mutable Frustum _bounds;
    mutable int _dirtyBits;
    Node* _node;
};

}

#endif