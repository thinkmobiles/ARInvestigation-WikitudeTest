//
// Created by simon on 08/04/15.
// Copyright (c) 2015 Wikitude. All rights reserved.
//


#ifndef RECOGNIZEDTARGET_H_
#define RECOGNIZEDTARGET_H_

#ifdef __cplusplus

#include <string>

#include "Matrix4.h"
#include "Geometry.h"


namespace wikitude { namespace sdk {
    
    namespace impl {
        
        class RecognizedTarget {
        public:
            RecognizedTarget(const std::string& name, const unsigned int distanceToTarget, const Rectangle<int>& targetRectInCameraFrame, const Matrix4& modelView, const Matrix4& projection);

            const std::string& getName() const;
            const unsigned int& getDistanceToTarget() const;
            const Rectangle<int>& getTargetPositionInCameraFrame() const;
            const Matrix4& getModelViewMatrix() const;
            const Matrix4& getProjectionMatrix() const;

        protected:
            const std::string&      _name;
            unsigned int            _distanceToTarget;
            const Rectangle<int>&   _targetRectInCameraFrame;
            Matrix4                 _modelView;
            Matrix4                 _projection;
        };
    }
    
    using impl::RecognizedTarget;
}}

#endif /* __cplusplus */

#endif
