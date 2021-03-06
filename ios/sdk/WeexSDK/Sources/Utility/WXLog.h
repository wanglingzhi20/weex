/**
 * Created by Weex.
 * Copyright (c) 2016, Alibaba, Inc. All rights reserved.
 *
 * This source code is licensed under the Apache Licence 2.0.
 * For the full copyright and license information,please view the LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, WXLogFlag) {
    WXLogFlagError      = 1 << 0,
    WXLogFlagWarning    = 1 << 1,
    WXLogFlagInfo       = 1 << 2,
    WXLogFlagDebug      = 1 << 3,
    WXLogFlagVerbose    = 1 << 4
};

/**
 *  Use Log levels to filter logs.
 */
typedef NS_ENUM(NSUInteger, WXLogLevel){
    /**
     *  No logs
     */
    WXLogLevelOff       = 0,
    
    /**
     *  Error only
     */
    WXLogLevelError     = WXLogFlagError,
    
    /**
     *  Error and warning
     */
    WXLogLevelWarning   = WXLogLevelError | WXLogFlagWarning,
    
    /**
     *  Error, warning and info
     */
    WXLogLevelInfo      = WXLogLevelWarning | WXLogFlagInfo,
    
    /**
     *  Error, warning, info and debug logs
     */
    WXLogLevelDebug     = WXLogLevelInfo | WXLogFlagDebug,
    
    /**
     *  Error, warning, info, debug and verbose
     */
    WXLogLevelVerbose   = WXLogLevelDebug | WXLogFlagVerbose,
    
    /**
     *  All
     */
    WXLogLevelAll       = NSUIntegerMax
};

/**
 *  External log protocol, which is used to output the log to the external.
 */
@protocol WXLogProtocol <NSObject>

@required

/**
 * External log level.
 */
- (WXLogLevel)logLevel;

- (void)log:(WXLogFlag)flag message:(NSString *)message;

@end

@interface WXLog : NSObject

+ (WXLogLevel)logLevel;

+ (void)setLogLevel:(WXLogLevel)level;

+ (NSString *)logLevelString;

+ (void)setLogLevelString:(NSString *)levelString;

+ (void)log:(WXLogFlag)flag file:(const char *)fileName line:(NSUInteger)line format:(NSString *)format, ... NS_FORMAT_FUNCTION(4,5);

+ (void)registerExternalLog:(id<WXLogProtocol>)externalLog;

@end

#define WX_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define WX_LOG(flag, fmt, ...)          \
do {                                    \
    [WXLog log:flag                     \
          file:WX_FILENAME              \
          line:__LINE__                 \
        format:(fmt), ## __VA_ARGS__];  \
} while(0)

#define WXLogVerbose(format, ...)       WX_LOG(WXLogFlagVerbose, format, ##__VA_ARGS__)
#define WXLogDebug(format, ...)         WX_LOG(WXLogFlagDebug, format, ##__VA_ARGS__)
#define WXLogInfo(format, ...)          WX_LOG(WXLogFlagInfo, format, ##__VA_ARGS__)
#define WXLogWarning(format, ...)       WX_LOG(WXLogFlagWarning, format, ##__VA_ARGS__)
#define WXLogError(format, ...)         WX_LOG(WXLogFlagError, format, ##__VA_ARGS__)
