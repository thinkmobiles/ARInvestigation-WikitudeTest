//
//  WTRendering.h
//  WikitudeCoreServices
//
//  Created by Andreas Schacherbauer on 14/06/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <QuartzCore/CADisplayLink.h>

/**
 * WTRenderingBlock represents a block object which is invoked every frame to perform the actual rendering.
 */
typedef void(^WTRenderingBlock)(CADisplayLink *displayLink);
