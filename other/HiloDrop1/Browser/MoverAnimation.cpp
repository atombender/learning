//===================================================================================
// Copyright (c) Microsoft Corporation.  All rights reserved.                        
//                                                                                   
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                    
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                       
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                          
// FITNESS FOR A PARTICULAR PURPOSE.                                                 
//===================================================================================


#include "StdAfx.h"
#include "MoverAnimation.h"

using namespace Hilo::AnimationHelpers;

const double MoverAnimation::m_acceleration = 8000;
const double MoverAnimation::m_accelerationRatio = 0.3;
const double MoverAnimation::m_decelerationRatio = 0.3;
const double MoverAnimation::m_duration = 1;

MoverAnimation::MoverAnimation()
{
}

MoverAnimation::~MoverAnimation()
{
}

// Create animated thumbnail cells
HRESULT MoverAnimation::CreateAnimatedThumbnailCells(const std::vector<ThumbnailCell>& prevThumbnailCells, const std::vector<ThumbnailCell>& currentThumbnailCells, D2D1_SIZE_F viewSize)
{
    m_animatedThumbnailCells.clear();
    for (auto currentCell = currentThumbnailCells.begin(); currentCell < currentThumbnailCells.end(); currentCell ++)
    {
        D2D1_RECT_F targetPosition = currentCell->position;
        D2D1_POINT_2F startPoint = D2D1::Point2F (viewSize.width, viewSize.height);
        for (auto prevCell =prevThumbnailCells.begin(); prevCell < prevThumbnailCells.end(); prevCell ++)
        {
            if (prevCell->control == currentCell->control )
            {
                // find it and get its location
                D2D1_RECT_F startPosition = prevCell->position;
                startPoint = D2D1::Point2F ((startPosition .right + startPosition .left )/2, 
                    (startPosition.bottom + startPosition.top )/2);
                break;
            }
        }
        D2D1_POINT_2F targetPoint = D2D1::Point2F ((targetPosition.right + targetPosition.left )/2, 
                    (targetPosition.bottom + targetPosition.top )/2);
        m_animatedThumbnailCells.push_back(AnimatedThumbnailCell(*currentCell, startPoint, targetPoint, D2D1::Point2F(0, 0), true));
    }

    return S_OK;
}

// Build storyboard for the animation
HRESULT MoverAnimation::BuildStoryboard()
{
    HRESULT hr = S_OK;
    ComPtr<IUIAnimationStoryboard> storyboard;

    m_animationPoints.clear();
     // Initialize animation variables if necessary
    if (nullptr == m_animationManager)
    {
        hr = Initialize();
    }
    if (SUCCEEDED (hr))
    {
        hr = m_animationManager->CreateStoryboard(&storyboard);
    }
    if (SUCCEEDED (hr))
    {
        for ( auto animatedCell = m_animatedThumbnailCells.begin(); animatedCell < m_animatedThumbnailCells.end(); animatedCell++)
        {
            D2D1_POINT_2F startPoint = animatedCell->start;
            D2D1_POINT_2F endPoint = animatedCell->end;
            LineAnimationVar animationVariable;
            // Create animation variables for corordinator x
            hr = m_animationManager->CreateAnimationVariable(startPoint.x, &(animationVariable.animationX));

            // Create animation variables for corordinator y
            if (SUCCEEDED (hr))
            {
                hr = m_animationManager->CreateAnimationVariable(startPoint.y, &(animationVariable.animationY));
            }
            if (SUCCEEDED (hr))
            {
                if (fabs(endPoint.x - startPoint.x) > fabs(endPoint.y - startPoint.y))
                {
                    hr = AddTransition (storyboard, animationVariable.animationX, endPoint.x, 
                      animationVariable.animationY, endPoint.y);
                }
                else
                {
                    hr = AddTransition (storyboard, animationVariable.animationY, endPoint.y, 
                      animationVariable.animationX, endPoint.x);
                }
            }
            m_animationPoints.insert(LineAnimationPair(animatedCell->cell.control, animationVariable));
        }
    }
   
    if (SUCCEEDED (hr))
    {
        hr = AnimationUtility::ScheduleStoryboard(storyboard);
    }
    return hr;
}

// Add transitions for animation variables individually
HRESULT MoverAnimation::AddTransition(IUIAnimationStoryboard* storyboard, IUIAnimationVariable* primaryVariable, double primaryValue, IUIAnimationVariable* secondVariable, double secondValue)
{
    // Check input params
    if (nullptr == storyboard || nullptr == primaryVariable || nullptr == secondVariable)
    {
        return E_POINTER;
    }

    ComPtr<IUIAnimationTransition> primaryTransition, secondTransition;

    // Create a transition for the primary animation variable
    HRESULT hr = m_transitionLibrary->CreateParabolicTransitionFromAcceleration(primaryValue, 0, m_acceleration, &primaryTransition);
    if (SUCCEEDED (hr))
    {
            hr = storyboard->AddTransition(primaryVariable, primaryTransition);
    }

    UI_ANIMATION_KEYFRAME keyFrame = 0;
    if (SUCCEEDED (hr))
    {
            hr =storyboard->AddKeyframeAfterTransition(primaryTransition, &keyFrame);
    }

    // Create a transition for the second animation variable
    if (SUCCEEDED(hr))
    {
        hr = m_transitionLibrary->CreateAccelerateDecelerateTransition(m_duration, secondValue, m_accelerationRatio, m_decelerationRatio, &secondTransition);
    }
    
    if (SUCCEEDED (hr))
    {
        hr = storyboard->AddTransitionBetweenKeyframes(secondVariable, secondTransition, UI_ANIMATION_KEYFRAME_STORYBOARD_START, keyFrame);
    }
    return hr;
}
