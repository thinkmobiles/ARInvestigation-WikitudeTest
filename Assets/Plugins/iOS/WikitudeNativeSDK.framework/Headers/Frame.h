//
//  Frame.h  
//
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef FRAME_H
#define FRAME_H

#ifdef __cplusplus

#include "Geometry.h"
#include "FrameColorSpace.h"

#include <cstdint>

namespace wikitude { namespace sdk {
    
    namespace impl {
        
        class Frame {
        public:
            Frame(FrameColorSpace frameColorSpace_, unsigned char* frameData_, int frameDataSize_, Size<int> const size_, float scaledWidth_, float scaledHeight_, std::int64_t presentationTimestampValue_, std::int32_t presentationTimestampTimescale_);
            virtual ~Frame();
            
            /**
             * Specifies the frame color space. Depending on the color space, frame data and data size differs.
             *
             * @return FrameColorSpace
             */
            const FrameColorSpace getFrameColorSpace() const;

            /**
             *
             *
             * @return data pointer to the frames
             */
            const unsigned char* getData() const;
            int getFrameDataSize() const;

            const Size<int>& getSize() const;

            const float getScaledWidth() const;
            const float getScaledHeight() const;

            std::int64_t getPresentationTimestampValue() const;
            std::int32_t getPresentationTimestampTimescale() const;
            
        private:
            FrameColorSpace     _frameColorSpace;
            unsigned char*      _frameData;
            int                 _frameDataSize;
            Size<int>           _size;
            float               _scaledWidth;
            float               _scaledHeight;
            std::int64_t        _presentationTimestampValue;
            std::int32_t        _presentationTimestampTimescale;
        };
    }
    using impl::Frame;
}}

#endif /* __cplusplus */

#endif
