//
//  WTEAGLView.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 8/29/12.
//
//

#import <UIKit/UIKit.h>


@class WTRenderer;
@interface WTEAGLView : UIView

@property (nonatomic, weak) WTRenderer                *renderer;

@end
