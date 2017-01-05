//
//  FrameColorSpace.h
//  FoundationSDK
//
//  Created by Andreas Schacherbauer on 22/03/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef FrameColorSpace_h
#define FrameColorSpace_h

#ifdef __cplusplus


namespace wikitude { namespace sdk {

    namespace impl {


        enum FrameColorSpace {
            /**
             * Represents a color space where image data is given in a YUV 420 format, arranged to be compliant to the NV21 standard.
             * The data size is frame width * frame height * 3/2, meaning full luminance resolution and half the size for chroma red * chroma blue
             *
             * On iOS this is represented by the kCVPixelFormatType_420YpCbCr8BiPlanarFullRange constant
             * On Android this is represented by the ImageFormat.YUV_420_888 constant. After that the frame needs to be converted to the NV21 format (replace U and V)
             */
            YUV_420_NV21,

            /**
             * Represents a color space where image data is given in a RGB format.
             * The data size is frame width * frame height * 3 (R, G and B channel).
             *
             * On iOS this is represented by the kCVPixelFormatType_24RGB constant
             * On Android this is represented by the ImageFormat.FLEX_RGB_888 constant
             */
            RGB
        };
    }
    using impl::FrameColorSpace;
}}

#endif /* __cplusplus */

#endif /* FrameColorSpace_h */
