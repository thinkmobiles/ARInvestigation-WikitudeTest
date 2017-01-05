//
//  WTCaptureDeviceManager.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 02/05/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>


NS_ASSUME_NONNULL_BEGIN

@class WTCaptureDeviceManager;

/**
 * WTCaptureDeviceManagerDelegate provides capture device manager specific methods that can be used to react to capture devcie manager specific state changes.
 */
@protocol WTCaptureDeviceManagerDelegate <NSObject>

/**
 * @brief Called whenever the capture device position changed.
 *
 * @param captureDeviceManager The capture device manger that managed the capture device position change.
 * @param activeCaptureDevicePosition The capture device position that is now active.
 */
- (void)captureDeviceManager:(WTCaptureDeviceManager *)captureDeviceManager didSwitchToActiveCaptureDevicePosition:(AVCaptureDevicePosition)activeCaptureDevicePosition;

/**
 * @brief Called whenever the capture device authorization status changed.
 *
 * @param captureDeviceManager The capture device manager that monitored the capture device authorization change.
 * @param authorizationStatus The authorization status that is now set.
 */
- (void)captureDeviceManager:(WTCaptureDeviceManager *)captureDeviceManager didChangeCaptureDeviceAuthorizationStatus:(AVAuthorizationStatus)authorizationStatus;

@end


/**
 * @brief WTCaptureDeviceManager can be used to change capture device specific settins at runtime.
 */
@interface WTCaptureDeviceManager : NSObject

/**
 * @brief The delegate object that is associated with this capture device manager object.
 */
@property (nonatomic, weak) id<WTCaptureDeviceManagerDelegate>          delegate;

/**
 * @brief The capture device position that is currently used or should be used.
 *
 * @return activeCaptureDevicePosition The capture device position that is currently active.
 */
@property (nonatomic, assign) AVCaptureDevicePosition                   activeCaptureDevicePosition;

/**
 * @brief The focus mode that is currently active or should be used.
 *
 * @return focusMode The focus mode that is currently active.
 */
@property (nonatomic, assign) AVCaptureFocusMode                        focusMode;

/**
 * @brief The auto focus range restriction that is currently active or should be used.
 *
 * @return autoFocusRangeRestriction The auto focus range restriction that is currently active.
 */
@property (nonatomic, assign) AVCaptureAutoFocusRangeRestriction        autoFocusRangeRestriction;

/**
 * @brief The zoom level that is currently active or should be used.
 *
 * @discussion Setting an unsupported value causes an internal error and does not change the currently set zoom level.
 *
 * @return zoomLevel The zoom level that is currently set.
 */
@property (nonatomic, assign) CGFloat                                   zoomLevel;

/**
 * @brief The maximal supported zoom level.
 *
 * @discussion This value should be read before setting a new zoom level so that a valid value is set.
 *
 * @return maxZoomLevel The maximal supported zoom level.
 */
@property (nonatomic, assign, readonly) CGFloat                         maxZoomLevel;

/**
 * @brief The torch mode that is currently active or should be used
 *
 * @return torchMode The torch mode that is currently active
 */
@property (nonatomic, assign) AVCaptureTorchMode                        torchMode;


/**
 * @brief The cameras horizontal field of view in degree.
 *
 * @return fieldOfView the current cameras horizontal field of view in degree
 */
@property (nonatomic, assign, readonly) CGFloat                         fieldOfView;

@end

NS_ASSUME_NONNULL_END
