//
//  EMBSubscriptionPurchaseFlow.h
//  Embrace
//
//  Created by Juan Pablo Crespi on 12/03/2018.
//  Copyright © 2018 embrace.io. All rights reserved.
//

#import "EMBCustomFlow.h"

/**
 This class is responsible for tracking app performance during subscription purchase flows.
 
 This class is thread-safe.
 */
@interface EMBSubscriptionPurchaseFlow : EMBCustomFlow

/**
 Starts a subscription purchase moment.
 
 This method should be called as soon as the user indicates an intent to purchase a subscription. This means that
 all information pertaining to the purchase (e.g. billing, payment, shipping) should already be known prior to
 invoking this method.
 
 @param orderId The ID that represents the subscription purchase order. This value is optional and, if present, will
                associate the value as a property of the moment.
 @param subscriptionType The recurrence factor (e.g. monthly, annual) of the subscription purchase. This value is
                         optional and, if present, will associate the value as a property of the moment.
 @param amount The total amount of the subscription purchase. This value is optional and, if present, will associate
               the value as a property of the moment.
 @param paymentType The payment system that will be fulfilling the subscription purchase (e.g. Google IAB, PayPal,
                    BrainTree). This value is optional and, if present, will associate the value as a property of
                    the moment.
 @param properties A map of Strings to Objects that represent additional properties to associate with the moment.
                   This value is optional. A maximum of 10 properties (not including the ones set via arguments to
                   this method) may be set.
 
 @return True if the operation was successful; false otherwise.
 */
- (NSString * _Nonnull)subscriptionPurchaseStartWithOrderId:(NSString * _Nullable)orderId subscriptionType:(NSString * _Nullable)subscriptionType amount:(NSNumber * _Nullable)amount paymentType:(NSString * _Nullable)paymentType properties:(NSDictionary * _Nullable)properties;

/**
 Ends the subscription purchase moment and generates an info log message that indicates that the subscription
 purchase completed.
 
 This method should be called once the subscription purchase has been confirmed.
 
 @return True if the operation was successful; false otherwise.
 */
- (BOOL)subscriptionPurchaseComplete;

/**
 Ends the subscription purchase moment and generates an error log message that indicates that the subscription
 purchase failed.
 
 This method should be called once the subscription purchase has been confirmed.
 
 @param message A message that explains the reason for why this operation failed. This value is optional and, if
                provided, will associate the value as a property of the error log message.
 
 @return True if the operation was successful; false otherwise.
 */
- (BOOL)subscriptionPurchaseFailWithMessage:(NSString * _Nullable)message;

@end
