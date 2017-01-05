//
//  WTTrackerManager.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 28/04/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>

#define WT_DEPRECATED_SINCE(__version__, __msg__) __attribute__((deprecated("Deprecated in Wikitude SDK " #__version__ ". " __msg__)))


NS_ASSUME_NONNULL_BEGIN

/**
 * WTCloudRecognitionServerRegion defines the possible cloud recognition server regions that are available.
 * The region should be set depending on where the final application will be used most likely.
 * If the region does not match the actual user location, longer round trip times should be expected.
 */
typedef NS_ENUM(NSInteger, WTCloudRecognitionServerRegion) {
    /**
     * WTCloudRecognitionServerRegion_Americas should be used when the user is currently in North or South America.
     */
    WTCloudRecognitionServerRegion_Americas,

    /**
     * WTCloudRecognitionServerRegion_Europe should be used when the user is currently in Europe, Africa or Middle East.
     */
    WTCloudRecognitionServerRegion_Europe,

    /**
     * WTCloudRecognitionServerRegion_China has to be used when the user is currently in China.
     */
    WTCloudRecognitionServerRegion_China
};


@class WTBaseTracker;
@class WTClientTracker;
@protocol WTClientTrackerDelegate;
@class WTCloudTracker;
@protocol WTCloudTrackerDelegate;

/**
 * WTTrackerManger provides factory methods to create certain tracker objects.
 */
@interface WTTrackerManager : NSObject

/**
 * @brief Returns a weak pointer to a newly created WTClientTracker object, configured for 2d tracking.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param clientTrackerURL A URL from where the client tracker should be loaded from. Client tracker can be loaded from the application bundle or a remote server.
 * @param extendedTargets An array containing string objects where each one of them represents an image target that should be tracked as extended target.
 * @param delegate A object that conforms to the WTClientTrackerDelegate protocol.
 * @return WTClientTracker * A pointer to a newly created WTClientTracker object.
 */
- (WTClientTracker *)create2DClientTrackerFromURL:(nonnull NSURL *)clientTrackerURL extendedTargets:(nullable NSArray *)extendedTargets andDelegate:(nonnull id<WTClientTrackerDelegate>)delegate;

/**
 * Deprecated - use create2DClientTrackerFromURL:extendedTargets:andDelegate: instead.
 * @deprecated 1.0.0
 */
- (WTClientTracker *)createClientTrackerFromURL:(nonnull NSURL *)clientTrackerURL extendedTargets:(nullable NSArray *)extendedTargets andDelegate:(nonnull id<WTClientTrackerDelegate>)delegate WT_DEPRECATED_SINCE(1.1.0, "Use create2DClientTrackerFromURL:extendedTargets:andDelegate: instead.");


/**
 * @brief Returns a weak pointer to a newly created WTClientTracker object, configured for 3d tracking.
 *
 * @discussion Callers need to make sure to retian the reference count e.g. by assigning to a strong property.
 *
 * @param trackingMapURL A URL from where the tracking map should be loaded from. Tracking maps can be loaded from the application bundle or a remote server.
 * @param delegate A object that conforms to the WTClientTrackerDelegate protocol.
 * @return WTClientTracker * A pointer to a newly created WTClientTracker object.
 */
- (WTClientTracker *)create3DClientTrackerFromURL:(nonnull NSURL *)trackingMapURL andDelegate:(nonnull id<WTClientTrackerDelegate>)delegate;

/**
 * @brief Returns a weak pointer to a newly created WTCloudTracker object.
 *
 * @discussion Callers need to make sure to retian the reference count e.g. by assigning to a strong property.
 *
 * @param authenticationToken The client token that is associated with your Wikitude cloud recogniition account.
 * @param targetCollectionId An identifier which target collection should be loaded on the Wikitude cloud recognition server.
 * @param extendedTargets An array containing string objects where each one of them represents an image target that should be tracked as extended target.
 * @param delegate A object that conforms to the WTCloudTrackerDelegate protocol.
 * @return WTCloudTracker * A pointer to anewly created WTCloudTracker object.
 */
- (WTCloudTracker *)createCloudTrackerWithToken:(nonnull NSString *)authenticationToken targetCollectionId:(nonnull NSString *)targetCollectionId extendedTargets:(nullable NSArray *)extendedTargets andDelegate:(id<WTCloudTrackerDelegate>)delegate;

/**
 * @brief Specifies the regional-distributed Wikitude server the SDK should contact when using cloud recognition.
 *
 * @discussion After this method is called, every cloud tracker that is created will contact the specified regional cloud recognition server. If a tracker was already created, it will still point to the previously defined region.
 * 
 * This method is typically called after the Wikitude Native SDK was created and the user location was determined if necessary.
 *
 * The Wikitude Native SDK will by default connect to WTCloudRecognitionServerRegion_Europe.
 *
 * @param cloudRecognitionServerRegion A constant of type WTCloudRecognitionServerRegion that specifies the regional cloud recognition server that should be contacted.
 */
- (void)setCloudRecognitionServerRegion:(WTCloudRecognitionServerRegion)cloudRecognitionServerRegion;

@end

NS_ASSUME_NONNULL_END
