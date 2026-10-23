#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {
            mWorldViewSize = mWindowSize*mWorldUnitsPerPixel;
          }

    // TODO: all of these:

    sf::Vector2f const windowToWorld(const sf::Vector2f& pWindow) { return pWindow*mWorldUnitsPerPixel + (mViewCenterWorld-(0.5f * mWorldViewSize)); };

    sf::Vector2f const worldToWindow(const sf::Vector2f& pWorld) { return (pWorld - (mViewCenterWorld-(0.5f * mWorldViewSize))) / mWorldUnitsPerPixel; };

    sf::Vector2f const windowPercentToWorld(const sf::Vector2f& pWindowPercent) { return pWindowPercent * mWorldViewSize + (mViewCenterWorld-(0.5f * mWorldViewSize)); };

    sf::Vector2f const worldToWindowPercent(const sf::Vector2f& pWorld) { return (pWorld - (mViewCenterWorld-(0.5f * mWorldViewSize))) / mWorldViewSize; };

    void translateWorld(const sf::Vector2f& deltaWorld) { mViewCenterWorld += deltaWorld; };

    void translateWindow(const sf::Vector2f& deltaScreen) { mViewCenterWorld += (deltaScreen * mWorldUnitsPerPixel); };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) { mViewCenterWorld += (deltaScreenPercent * mWorldViewSize); };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) { mViewCenterWorld += ((pWindow - worldToWindow(pWorld)) * mWorldUnitsPerPixel); };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) { mViewCenterWorld += ((pWindowPercent - worldToWindowPercent(pWorld))
                                                                                            * mWorldViewSize); };

    void setCameraCenter(const sf::Vector2f& pWorld) { mViewCenterWorld = pWorld; };

    sf::Vector2f const getCameraCenter() const { return mViewCenterWorld; };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel

    sf::Vector2f mWorldViewSize;    // size of the camera in world coords
};

#endif  // CAMERA_H
