//
//  EMBConstants.h
//  Embrace
//
//  Created by Brian Wagner on 9/13/16.
//  Copyright © 2016 embrace.io. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, EMBLogLevel) {
    EMBLogLevelNone = 0,
    EMBLogLevelDebug,
    EMBLogLevelInfo,
    EMBLogLevelWarning,
    EMBLogLevelError
};

typedef NS_ENUM(NSInteger, EMBSeverity) {
    EMBSeverityError = 0,
    EMBSeverityWarning,
    EMBSeverityInfo
};

extern NSString *const EMBBundleIdentifier;
