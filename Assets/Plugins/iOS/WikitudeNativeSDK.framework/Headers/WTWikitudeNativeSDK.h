//
//  WikitudeNativeSDK.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 18/04/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * WTCustomUpdateHandler is used when rendering mode is set to WTRenderingMode_Internal. Please refer to -wikitudeNativeSDKNeedsExternalUpdateHandler: for more information
 */
typedef void(^WTCustomUpdateHandler)(void);

/**
 * WTCustomDrawHandler is used when rendering mode is set to WTRenderingMode_Internal. Please refer to -wikitudeNativeSDKNeedsExternalDrawHandler: for more information
 */
typedef void(^WTCustomDrawHandler)(void);


/**
 * WTWikitudeUpdateHandler is used when rendering mode is set to WTRenderingMode_External. Please refer to -wikitudeNativeSDK:didCreatedExternalUpdateHandler: for more information
 */
typedef void(^WTWikitudeUpdateHandler)(void);

/**
 * WTWikitudeDrawHandler is used when rendering mode is set to WtRenderingMode_External. Please refer to -wikitudeNativeSDK:didCreatedExternalDrawHandler: for more information
 */
typedef void(^WTWikitudeDrawHandler)(void);


/**
 * WTRenderingMode defines how the Wikitude Native SDK should render.
 */
typedef NS_ENUM(NSUInteger, WTRenderingMode) {
    /**
     * WTRenderingMode_Internal Using rendering mode internal, the Wikitude Native SDK is setting up a rendering loop and additional custom update and draw handler can be supplied using the WTWikitudeNativeSDKDelegate
     */
    WTRenderingMode_Internal,
    /**
     * WTRenderingMode_External Using rendering mode external, the Wikitude Native SDK is driven by an external render loop. It's the external renderers responsibility to start an appropriate render loop (30 or 60 fps) and to pause and resume it when the application enters background/foreground.
     */
    WTRenderingMode_External
};

@class WTWarning;
@class WTEAGLView;
@class WTRenderer;
@class WTTrackerManager;
@class WTTrackingMapRecorder;
@class WTCaptureDeviceManager;
@class WTStartupConfiguration;
@class WTWikitudeNativeSDK;

/**
 * WTWikitudeNativeSDKDelegate is used to handle information exchange between the Wikitude Native SDK and internal/external renderer as well as to inform about internal errors that occured during this conversation.
 *
 * Although all methods are marked as optional, all internal or extenal rendering related methods must be implemented. If not, an appropriate error is reported through the -wikitudeNativeSDK:didEncounterInternalError method.
 */
@protocol WTWikitudeNativeSDKDelegate <NSObject>
@optional
/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to external, this method is called to pass a Wikitude internal update block to the external renderer.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that created the update handler.
 * @param updateHandler A ObjC block object that needs to be called every frame in order to update the Wikitude Native SDK internally. If this handler is not called, no computer vision related updates are done.
 */
- (void)wikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK didCreatedExternalUpdateHandler:(WTWikitudeUpdateHandler)updateHandler;

/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to external, this method is called to pass a Wikitude internal draw handler to the external renderer.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that created the draw handler
 * @param drawHandler A ObjC block object that needs to be called every frame in order to draw the camera background
 */
- (void)wikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK didCreatedExternalDrawHandler:(WTWikitudeDrawHandler)drawHandler;

/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to external, this method is called to retrief the OpenGL ES 2 view size.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that requests the eagl view size
 * @return CGRect A rect representing the current OpenGL ES 2 view size. This method needs to return a non zero rect.
 */
- (CGRect)eaglViewSizeForExternalRenderingInWikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK;

/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to external, this method is called to retrief the EAGLContext that should be used to perform camera related OpenGL ES 2 calls.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that needs an EALGContext object
 * @return EAGLContext The EAGLContext object that should be used to perform OpenGL ES 2 calls that are camera related. Note that this context can be a shared context from another EAGLContext object.
 */
- (EAGLContext *)eaglContextForVideoCameraInWikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK;

/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to external, this method is called to retrief the EAGLContext object that should be used to perform offscreen rendering related OpenGL ES 2 calls.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that needs an EALGContext object for video to texture rendering
 * @return EAGLContext The EAGLContext object that manages the OpenGL ES 2 texture which is the render target
 */
- (EAGLContext *)eaglContextForVideoCameraToTextureRenderingInWikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK;

/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to internal, this method is called to retrief a custom update handler object. The handler is then invoked every frame to update Wikitude external logic.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that needs an external update handler
 * @return WTCustomUpdateHandler A custom upadte hanlder object that is invoked every frame by the Wikitude Native SDK
 */
- (nonnull WTCustomUpdateHandler)wikitudeNativeSDKNeedsExternalUpdateHandler:(WTWikitudeNativeSDK *)wikitudeNativeSDK;

/**
 * @brief Called during -start:completion:
 *
 * When rendering mode is set to internal, this mehtod is called to retrief a custom draw handler object. The handler is then invoked every frame to issue Wikitude external draw commands in OpenGL ES 2.
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that needs an externla draw handler
 * @return  WTCustomDrawHandler A custom draw handler object that is invoked every by the Wikitude Native SDK
 */
- (nonnull WTCustomDrawHandler)wikitudeNativeSDKNeedsExternalDrawHandler:(WTWikitudeNativeSDK *)wikitudeNativeSDK;

/**
 * @brief Called every time the Wikitude Native SDK encounters any internal warnings
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that encountered the internla warning
 * @param warning A warning object that contains more information about a specific warning
 */
- (void)wikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK didEncounterInternalWarning:(WTWarning *)warning;

/**
 * @brief Called every time the Wikitude Native SDK encounters any internl errors
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that encountered the internal error
 * @param error A error object that contains more information about a specific error
 */
- (void)wikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK didEncounterInternalError:(NSError *)error;

@end


/**
 * @brief WTWikitudeNativeSDK is the main entry point when using the Wikitude Native SDK.
 *
 * WTWikitudeNativeSDK coordinates how camera rendering is done (internal/external rendering), how tracker creation is handled and how capture device specific settings can be changed.
 */
@interface WTWikitudeNativeSDK : NSObject

/**
 * Returns the rendering mode that was set when initWithRenderingMode:delegate: was called
 */
@property (nonatomic, assign, readonly) WTRenderingMode                         renderingMode;

/**
 * Return the current SDK running State. YES if the SDK is running, false otherwise.
 */
@property (nonatomic, assign, readonly) BOOL                                    isRunning;

/**
 * @brief Returns the Wikitude Native SDK version as a formatted string.
 *
 * The format is 'major'.'minor'.'bugfix' e.g. 1.0.1
 */
+ (NSString *)sdkVersion;

/**
 * @brief The designated initializer to create an object of this class.
 *
 * @param renderingMode The rendering mode that should be used by the Wikitude Native SDK. See WTRenderingMode for more information about the different rendering modes.
 * @param delegate The object that acts as a delegate for the Wikitude Native SDK object.
 * @return WTWikitudeNativeSDK An object of type WTWikitudeNativeSDK.
 */
- (instancetype)initWithRenderingMode:(WTRenderingMode)renderingMode delegate:(id<WTWikitudeNativeSDKDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/**
 * @brief Factory method to get a pre configured OpenGL ES 2 View object that can be added to the view hierarchy.
 *
 * This method is only relevant when using the Wikitude Native SDK with WTRenderingMode_Internal.
 * After retrieving a pointer to a WTEAGLView, the renderer property has to be set before -start:completion: is called.
 *
 * @discussion Please note that the returned pointer is of type weak and the view has either to be added to the view hierarchy within the scope of the calling method or retained (assign to a strong property) until the view was added to the view hierarchy.
 *
 * @return WTEAGLView A weak pointer to a Open GL ES 2 view.
 */
- (WTEAGLView *)createEAGLView;

/**
 * @brief Factory method to get a pre configured render object that is used by a WTEAGLView object.
 *
 * This method is only relevant when using the Wikitude Native SDK with WTRenderingMode_Internal.
 *
 * @discussion A WTRenderer object coordinates and initializes internal rendering. Please note that the returned object is already fully configured and no customization is needed.
 *
 * @return WTRenderer A weak pointer to a WTRenderer object.
 */
- (WTRenderer *)createRenderer;

/**
 * @brief Provides access to a WTTrackerManager object that coordinates tracker creation
 *
 * Please refer to the WTTrackerManager documentation for more information about how to create different tracker types.
 *
 * @return A object of type WTTrackerManager that provides factory methods to create different tracker types.
 */
- (WTTrackerManager *)trackerManager;

/**
 * @brief Provides access to a WTTrackingMapRecorder object that coordinates recording of 3D tracking maps.
 *
 * Please refer to the WTTrackingMapRecorder documentation for more information about how to record 3D tracking maps.
 *
 * @return A object of type WTTrackingMapRecorder to control 3D tracking map recording.
 */
- (WTTrackingMapRecorder *)trackingMapRecorder;

/**
 * @brief Provides access to a WTCaptureDeviceManager if and only if the Wikitude Native SDK is currently running.
 *
 * @discussion WTCaptureDeviceManager objects can be used to change camera specific settings during Wikitude Native SDK runtime. To start the Wikitude Native SDK with non default camera parameter, please use the WTStartupConfiguration object that is passed to the startupHandler object when calling -start:completion:
 *
 * @return A valid pointer to a WTCaptureDeviceManger object if the Wikitude Native SDK is running, nil otherwise.
 */
- (nullable WTCaptureDeviceManager *)captureDeviceManager;

/**
 * @brief Enables SDK features based on the given license key.
 *
 * @discussion Depending on the license key, differnt types of watermarks are drawn, depending on the usage of licensed features or not. When this method is not called at all, only the camera stream is rendered but nothing else will be enabled. To try out all Wikitude Native SDK features, download a trial license from our webpage and call this method with the downloaded key.
 *
 * @param licenseKey Your developer key, provided with your licence information.
 */
- (void)setLicenseKey:(NSString *)licenseKey;

/**
 * @brief Starts Wikitude Native SDK rendering and internal updates.
 *
 * This method has to be called whenever the hosting view controllers view becomes visible or the application becomes active.
 *
 * @discussion Since some Wikitude Native SDK internal components start asynchronously, isRunning might be set to YES but an internal error is reported once a component encounters an error.
 *
 * @param startupHandler A block object that can be used to alter the Wikitude Native SDK starup behaviour
 * @param completionHandler A block object that can be used to evaluate if the Wikitude Native SDK could be started or not with the given starupt configuration.
 */
- (void)start:(nullable void (^)(WTStartupConfiguration *configuration))startupHandler completion:(void (^)(BOOL isRunning, NSError *error))completionHandler;

/**
 * @brief Stops Wikitude Native SDK rendering and internal updates.
 *
 * This method has to be called whenever the hosting view controllers view becomes not visible anymore or the application resigns active state.
 *
 * @discussion When the hosting application resigns active state and the Wikitude Native SDK is still running, the behaviour is undefined.
 */
- (void)stop;

/**
 * @brief Call this method when the hosting view controller changes it's size.
 *
 * @discussion This method has to be called every time the rendering view, which is used by the Wikitude Native SDK, changes it's size. It might also be necessary to call this mehtod after the Wikitude Native SDK was created and the final view layout was not set yet.
 *
 * @param size The new size of the Wikitude Native SDK rendering view.
 * @param transitionCoordinator The transiton coordinator that coordinates transitioning to the new size
 */
- (void)shouldTransitionToSize:(CGSize)size withTransitionCoordinator:(nullable id<UIViewControllerTransitionCoordinator>)transitionCoordinator;

/**
 * @brief Clears all internal caches used by the SDK.
 */
- (void)clearCache;

@end

NS_ASSUME_NONNULL_END
