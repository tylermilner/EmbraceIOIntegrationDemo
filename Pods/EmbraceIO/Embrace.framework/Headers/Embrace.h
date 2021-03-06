//
//  Embrace.h
//  Embrace
//
//  Created by Brian Wagner on 9/12/16.
//  Copyright © 2016 embrace.io. All rights reserved.
//

#import <UIKit/UIKit.h>

FOUNDATION_EXPORT double EmbraceVersionNumber;
FOUNDATION_EXPORT const unsigned char EmbraceVersionString[];

#import "EMBConstants.h"
#import "EMBCustomFlow.h"
#import "EMBPurchaseFlow.h"
#import "EMBRegistrationFlow.h"
#import "EMBSubscriptionPurchaseFlow.h"

// Public Embrace API for use by developers

/**
 The EMBDelegate is used to notify the application of updates from the Embrace.io SDK. Currently the only update that will be
 delivered is whether the Embrace.io SDK is active for the given app launch.
 */
@protocol EmbraceDelegate <NSObject>

@optional

/**
 Optional callback that gets called to inform the user whether the Embrace.io SDK is enabled or disabled for the current
 app user. It is also called when the status changes from enabled to disabled or vice versa.
 
 @param enabled A bool indicating whether the Embrace.io SDK is on or off for the current application instance.
 */
- (void)embraceSDKIsEnabled:(BOOL)enabled;

@end

@interface Embrace : NSObject

/**
 Optional delegate property that can be set to receive callbacks about the Embrace.io SDK's operations
 */
@property (nonatomic, weak) id<EmbraceDelegate> delegate;

/**
 Returns the shared `Embrace` singleton object.
 */
+ (instancetype)sharedInstance;

/**
 Performs the initial setup of the Embrace SDK with the provided API key.
 
 This puts in place device and network monitoring, kicks off reporting, and marks the beginning of the "App Startup" event.
 
 @param apiKey The unique Embrace API key that identifies your application.
 */
- (void)startWithKey:(NSString *)apiKey;

/**
 Marks the end of the "App Startup" event.
 */
- (void)endAppStartup;

/**
 Starts recording data for an app moment with the provided name.
 
 If another app moment with the provided name is in progress, it will be overwritten.
 
 @param name The name used to identify the app moment
 */
- (void)beginEventWithName:(NSString *)name DEPRECATED_MSG_ATTRIBUTE("Please replace calls to start app moments with methods of the form startMomentWithName:");
- (void)startMomentWithName:(NSString *)name;

/**
 Starts recording data for an app moment with the provided name and identifier.
 
 Identifiers can be used to separately log data for different instances of a given moment, e.g. an image download.
 All moments will be aggregated by name—the identifier is purely for avoiding naming collisions.
 A start event with a given name, identifier pair will overwrite any existing app moments with the same name and identifier.
 
 @param name The name used to identify the moment.
 @param identifier An identifier that is combined with the name to create a unique key for the moment.
 */
- (void)beginEventWithName:(NSString *)name identifier:(NSString *)identifier DEPRECATED_MSG_ATTRIBUTE("Please replace calls to start app moments with methods of the form startMomentWithName:identifier:");
- (void)startMomentWithName:(NSString *)name identifier:(NSString *)identifier;

/**
 Starts recording data for an app moment with the provided name, optional identifier, and option to take a screenshot.
 Screenshots will be taken if the SDK detects that the moment is late (taking longer than it should).
 Note: screenshots will be rate-limited, so if two moments trigger screenshots within 1 second of each other, only
 one screenshot will be taken.
 
 @param name The name used to identify the moment.
 @param identifier An identifier that is combined with the name to create a unique key for the moment (can be nil).
 @param allowScreenshot A flag for whether to enable screenshot functionality if the moment is late (defaults to YES).
 */
- (void)beginEventWithName:(NSString *)name identifier:(NSString *)identifier allowScreenshot:(BOOL)allowScreenshot DEPRECATED_MSG_ATTRIBUTE("Please replace calls to start app moments with methods of the form startMomentWithName:identifier:allowScreenshot:");
- (void)startMomentWithName:(NSString *)name identifier:(NSString *)identifier allowScreenshot:(BOOL)allowScreenshot;

/**
 Starts recording data for an app moment with the provided name, optional identifier, and optional key/value metadata
 
 @param name The name used to identify the moment.
 @param identifier An identifier that is combined with the name to create a unique key for the moment (can be nil).
 @param properties An optional dictionary containing metadata about the moment to be recorded (limited to 10 keys).
 */
- (void)startMomentWithName:(NSString *)name identifier:(NSString *)identifier properties:(NSDictionary *)properties;

/**
 Starts recording data for an app moment with the provided name, optional identifier, screenshot flag, and optional key/value metadata
 
 @param name The name used to identify the moment.
 @param identifier An identifier that is combined with the name to create a unique key for the moment (can be nil).
 @param allowScreenshot A flag for whether to take a screenshot if the moment is late (defaults to YES).
 @param properties An optional dictionary containing metadata about the moment to be recorded (limited to 10 keys).
 */
- (void)beginEventWithName:(NSString *)name identifier:(NSString *)identifier allowScreenshot:(BOOL)allowScreenshot properties:(NSDictionary *)properties DEPRECATED_MSG_ATTRIBUTE("Please replace calls to start app moments with methods of the form startMomentWithName:identifier:allowScreenshot:properties:");
- (void)startMomentWithName:(NSString *)name identifier:(NSString *)identifier allowScreenshot:(BOOL)allowScreenshot properties:(NSDictionary *)properties;

/**
 Stops recording data for an app moment with the provided name.
 
 This marks the moment as "completed."
 If no moment is found with the provided name (and an empty identifier), this call will be ignored.
 Additionally, if an app moment was started with a name and identifier, the same identifier must be used to end it.
 
 @param name The name used to identify the moment.
 */
- (void)endEventWithName:(NSString *)name DEPRECATED_MSG_ATTRIBUTE("Please replace calls to end app moments with methods of the form endMomentWithName:");
- (void)endMomentWithName:(NSString *)name;

/**
 Stops recording data for an app moment with the provided name and identifier.
 
 The moment that has the given name, identifier pair will be marked as "completed."
 If no moment is found with the given name AND identifier, this call will be ignored.
 
 @param name The name used to identify the moment.
 @param identifier An identifier that is combined with the name to uniquely identify the moment.
 */
- (void)endEventWithName:(NSString *)name identifier:(NSString *)identifier DEPRECATED_MSG_ATTRIBUTE("Please replace calls to end app moments with methods of the form endMomentWithName:identifier:");
- (void)endMomentWithName:(NSString *)name identifier:(NSString *)identifier;

/**
 Logs an event in your application for aggregation and debugging on the Embrace.io dashboard.
 
 Events are grouped by name and severity.
 
 @param name The name of the message, which is how it will show up on the dashboard
 @param severity Will flag the message as one of info, warning, or error for filtering on the dashboard
 */
- (void)logMessage:(NSString *)name withSeverity:(EMBSeverity)severity;

/**
 Logs an event in your application for aggregation and debugging on the Embrace.io dashboard
 with an optional dictionary of up to 10 properties.
 
 @param name The name of the message, which is how it will show up on the dashboard
 @param severity Will flag the message as one of info, warning, or error for filtering on the dashboard
 @param properties An optional dictionary of up to 10 key/value pairs
 */
- (void)logMessage:(NSString *)name withSeverity:(EMBSeverity)severity properties:(NSDictionary *)properties;

/**
 Logs an event in your application for aggregation and debugging on the Embrace.io dashboard
 with an optional dictionary of up to 10 properties and the ability to enable or disable a screenshot.
 
 @param name The name of the message, which is how it will show up on the dashboard
 @param severity Will flag the message as one of info, warning, or error for filtering on the dashboard
 @param properties An optional dictionary of up to 10 key/value pairs
 @param takeScreenshot A flag for whether the SDK should take a screenshot of the application window to display on the dashboard
 */
- (void)logMessage:(NSString *)name withSeverity:(EMBSeverity)severity properties:(NSDictionary *)properties takeScreenshot:(BOOL)takeScreenshot;

/**
 Logs an informative message to the Embrace.io API for aggregation and viewing on the dashboard.
 
 @param message The message used to find the log later, which is how it will be aggregated on the web dashboard
 @param properties An optional dictionary of custom key/value properties to be sent with the message
 */
- (void)logInfoMessage:(NSString *)message properties:(NSDictionary *)properties DEPRECATED_MSG_ATTRIBUTE("Please replace calls to log info messages with methods of the form logMessage:withSeverity:");

/**
 Logs a warning message to the Embrace.io API for aggregation and viewing on the dashboard. Unlike info messages,
 warning messages will be accompanied by a screenshot and stack trace. The screenshot can be disabled with the `screenshot` argument.
 
 @param message The message used to find the warning later, which will be combined with the stack trace to aggregate the logs on the dashboard view.
 @param screenshot A flag for whether to take a screenshot or not.
 @param properties An optional dictionary of custom key/value properties to be sent with the warning log.
 */
- (void)logWarningMessage:(NSString *)message screenshot:(BOOL)screenshot properties:(NSDictionary *)properties DEPRECATED_MSG_ATTRIBUTE("Please replace calls to log warning messages with methods of the form logMessage:withSeverity:");

/**
 Logs an error message to the Embrace.io API for aggregation and viewing on the dashboard. Unlike info messages,
 error messages will be accompanied by a screenshot and stack trace. The screenshot can be disabled with the `screenshot` argument.
 
 @param message The message used to find the error later, which will be combined with the stack trace to aggregate the logs on the dashboard view.
 @param screenshot A flag for whether to take a screenshot or not.
 @param properties An optional dictionary of custom key/value properties to be sent with the error log.
 */
- (void)logErrorMessage:(NSString *)message screenshot:(BOOL)screenshot properties:(NSDictionary *)properties DEPRECATED_MSG_ATTRIBUTE("Please replace calls to log error messages with methods of the form logMessage:withSeverity:");

/**
 Logs an Error or NSError object to the Embrace.io API for aggregation on the dashboard. These errors will be treated similarly to
 error log messages, but the serialization will be done by Embrace. During the serialization calls, the error description,
 reason, domain, and code will be logged as properties. As with error logs, a stack trace will be taken, and
 optional screenshots and error properties can be specified.
 
 @param error The handled error object, which will be serialized and combined with the stack trace to aggregate the errors on the dashboard view.
 @param screenshot A flag for whether to take a screenshot or not.
 @param properties An optional dictionary of custom key/value properties to be sent with the error log.
 */
- (void)logHandledError:(NSError *)error screenshot:(BOOL)screenshot properties:(NSDictionary *)properties;

/**
 Logs a custom message within this session for the Embrace dashboard to surface on the Session Timeline and within
 the Activity Log.
 
 This will NOT trigger an http request to the Embrace.io backend and is useful for adding additional context to the
 actions a user performed within a session. Good uses for breadcrumbs could be your app's console error output
 or notes that significant events (add item to cart, start conversation, receive push notification) occurred.
 
 @param message The message that will be displayed within the session's Activity Log on the dashboard.
 */
- (void)logBreadcrumbWithMessage:(NSString *)message;

/**
 Associates the current app user with an internal identifier (e.g. your system's uid) to be made searchable at a later date.
 
 @param userId An internal identifier for the given user.
 */
- (void)setUserIdentifier:(NSString *)userId;

/**
 Resets the internal identifier for the current app user.
 */
- (void)clearUserIdentifier;

/**
 Associates the current app user with a username to be made searchable at a later date.
 
 @param username The current app user's associated username.
 */
- (void)setUsername:(NSString *)username;

/**
 Removes the username associated with the current app user.
 */
- (void)clearUsername;

/**
 Associates the current app user with an email address to be made searchable at a later date.
 
 @param email The current app user's associated email address.
 */
- (void)setUserEmail:(NSString *)email;

/**
 Removes the email address associated with the current app user.
 */
- (void)clearUserEmail;

/**
 Marks the current app user as a paying user.
 
 This is used for cohorting and segmentation in the dashboard.
 */
- (void)setUserAsPayer;

/**
 Marks the current app user as a non-paying user (the default).
 */
- (void)clearUserAsPayer;

/**
 Sets a custom persona for the current app user.
 
 This accepts various custom values — use whichever is applicable to your app.
 */
- (void)setUserPersona:(NSString *)persona;

/**
 Removes the given custom persona for the current app user.
 */
- (void)clearUserPersona:(NSString *)persona;

/**
 Logs enhanced metrics for a given URLSessionTask
 */
- (void)logURLSessionTaskMetrics:(NSURLSessionTaskMetrics *)metrics forURLSessionTask:(NSURLSessionTask *)task;

/**
 Inform Embrace that a web view began a request that you'd like to have monitored. In order for data to be captured,
 ensure that you call `logWebViewCompletedRequest:` after the request is finished.
 
 We recommend calling this in the `- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType`
 callback of your UIWebViewDelegate.
 
 @param request The NSURLRequest whose performance you'd like to instrument.
 */
- (void)logWebViewBeganRequest:(NSURLRequest *)request;

/**
 Inform Embrace that a web view completed a request. The `logWebViewBeganRequest:` method must have been called
 when this request was first created in order for instrumentation to function properly.
 
 We recommend calling this in the `- (void)webViewDidFinishLoad:(UIWebView *)webView` callback of your
 UIWebViewDelegate.
 
 @param webView The UIWebView whose request you'd like to monitor.
 */
- (void)logWebViewCompletedRequest:(UIWebView *)webView;

/**
 Inform Embrace that a web view completed a request. The `logWebViewBeganRequest:` method must have been called
 when this request was first created in order for instrumentation to function properly.
 
 We recommend calling this in the `- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error` callback of your
 UIWebViewDelegate.
 
 @param webView The UIWebView whose request you'd like to monitor.
 @param error The NSError you'd like to monitor.
 */
- (void)logWebViewCompletedRequest:(UIWebView *)webView withError:(NSError *)error;

- (void)setDebuggingEnabled:(BOOL)enabled;

@end
