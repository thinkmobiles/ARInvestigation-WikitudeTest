//
//  WTTrackingMapRecorder.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 01/10/15.
//  Copyright © 2015 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

/**
 * WTTrackingMapRecordingStartupHandler represents a block which contains more information about the started map recording session.
 */
typedef void(^WTTrackingMapRecordingStartupHandler)(BOOL isRecording, NSError * _Nullable error);

/**
 * WTTrackingMapRecordingCompletionHandler represents a block which contains more informaiton about a saved tracking map.
 */
typedef void(^WTTrackingMapRecordingCompletionHandler)(NSURL * _Nullable trackingMapURL, NSError * _Nullable error);


/**
 * WTTrackingMapRecordingQuality defines the possible states in which a running 3d tracking map recording session can be.
 */
typedef NS_ENUM(NSInteger, WTTrackingMapRecordingQuality) {
    /**
     * WTTrackingMapRecordingQuality_Bad indicates that the current 3d tracking map can not be used to successfully recognize any objects in the recorded scene.
     */
    WTTrackingMapRecordingQuality_Bad = -1,

    /**
     * WTTrackingMapRecordingQuality_Average indicates that the current 3d tracking map can be used to recognize objects, but the results might not be very satisfying.
     */
    WTTrackingMapRecordingQuality_Average,

    /**
     * WTTrackingMapRecordingQuality_Good indicates that the currently recorded 3d tracking map includes enough information so that it's content can be recognized at a later point in time.
     */
    WTTrackingMapRecordingQuality_Good
};


@class WTTrackableObject;
@class WTTrackingMapRecorder;

/**
 * @Brief WTTrackingMapRecorderDelegate provides methods that inform about an active 3d tracking map recording session.
 */
@protocol WTTrackingMapRecorderDelegate <NSObject>

@optional
/**
 * @Brief Called whenever an active 3d tracking map recording session changes it's quality.
 *
 * @discussion The new recording quality might be worse than the previous one, meaning that a new value doesn't has to be better than a previous one.
 *
 * @param trackingMapRecorder The WTTrackingMapRecorder object that changed it's traching quality
 * @param oldTrackingQuality The previously tracking quality before the new value was registered internally
 * @param newTrackingQuality The new tracking quality
 */
- (void)trackingMapRecorder:(WTTrackingMapRecorder *)trackingMapRecorder didChangeTrackingMapRecordingQualityFrom:(WTTrackingMapRecordingQuality)oldTrackingQuality toQuality:(WTTrackingMapRecordingQuality)newTrackingQuality;

/**
 * @Brief Called whenever the state of a active recording session changes.
 *
 * @discussion This method can be used to detect interruptions (tracking got lost) during a recording sessions. Once the recording was interrupted, -isRecording will return NO and -stopTrackingMapRecording/-startTrackingMapRecording has to be called in order to start a new tracking map recording session.
 *
 * @param trackingMapRecorder The WTTrackingMapRecorder object that changed it's recording state
 * @param isRecording Indicates if the recording is running or not
 */
- (void)trackingMapRecorder:(WTTrackingMapRecorder *)trackingMapRecorder didUpdateTrackingMapRecordingState:(BOOL)isRecording;

/**
 * @Brief Called whenever an active 3d tracking map recording session changed it's tracking information.
 *
 * @discussion The new tracking map recording information can be used to already place objects in 3D space to e.g. visualize the recording process.
 *
 * @param trackingMapRecorder The WTTrackingMapRecorder object that updated it's recording data
 * @param trackingMap An object that represents the current recording state. This can be used to already draw augmentations while the recording is running.
 */
- (void)trackingMapRecorder:(WTTrackingMapRecorder *)trackingMapRecorder didUpdateTrackingMapRecording:(WTTrackableObject *)trackingMap;

@end


/**
 * WTTrackingMapRecorder provides the functionality to record so called 'Tracking Maps' that are needed for 3D tracking.
 *
 */
@interface WTTrackingMapRecorder : NSObject

/**
 * Delegate pointer for a WTTrackingMapRecorder object.
 */
@property (nonatomic, weak) id<WTTrackingMapRecorderDelegate>               delegate;

/**
 * Starts a new 3D tracking map recording session.
 *
 * @discussion This method returns immediately and starts the recording session in the background.
 *
 * @param startupHandler A block that is executed when the recording actually started.
 */
- (void)startTrackingMapRecording:(WTTrackingMapRecordingStartupHandler)startupHandler;

/**
 * Use this method to check if a 3D tracking map recording session is currently running or not.
 *
 * @return YES is a 3D tracking map recording session is currently running or not.
 */
- (BOOL)isRecording;

/**
 * Stops an already running 3D tracking map recording session.
 *
 * @param mapName The name of the 3D tracking map file.
 * @param completionHandler A completion handler that is called once the 3D tracking map could be saved to disk or not.
 */
- (void)stopTrackingMapRecording:(NSString *)mapName completion:(WTTrackingMapRecordingCompletionHandler)completionHandler;


/**
 * Cancels an already running 3D tracking map recording session. 
 * Calling this method without a running 3D tracking map recording session has no effect.
 *
 * Note: This method returns immediately.
 *
 * @discussion Once the running 3D tracking map recording session is canceled, it can't be restarted nor saved.
 */
- (void)cancelTrackingMapRecording;

@end

NS_ASSUME_NONNULL_END
