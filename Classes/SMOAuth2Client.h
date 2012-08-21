/*
 * Copyright 2012 StackMob
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "AFHTTPClient.h"

@class SMCustomCodeRequest;
@class SMRequestOptions;

/**
 An interface for creating OAuth2 signed requests.
 */
@interface SMOAuth2Client : AFHTTPClient

@property (nonatomic, copy) NSString *version;
@property (nonatomic, copy) NSString *publicKey;
@property (nonatomic, copy) NSString *apiHost;
@property (nonatomic, copy) NSString *accessToken;
@property (nonatomic, copy) NSString *macKey;

/**
 Initialize method used by <SMUserSession>.
 @param version The API version of your StackMob application which this client instance should use.
 @param scheme Either http or https
 @param apiHost The host to connect to for API requests.
 @param publicKey Your StackMob application's OAuth2 public key.
 @return An instance of `SMOAuth2Client`
 */
- (id)initWithAPIVersion:(NSString *)version 
                   scheme:(NSString *)scheme
                  apiHost:(NSString *)apiHost
                publicKey:(NSString *)publicKey;

/**
 Creates a signed request using the given parameters.
 
 @param method The HTTP verb to use, either `POST`,`GET`, `PUT`, or `DELETE`.
 @param path The REST path.
 @param parameters A dictionary to be used as the body of the request.
 
 @return A signed request to be placed on an operation queue.
 */
- (NSMutableURLRequest *)requestWithMethod:(NSString *)method 
                                       path:(NSString *)path 
                                 parameters:(NSDictionary *)parameters;

/**
 Creates a signed request for a custom code method using the given parameters.
 
 @param request An instance of <SMCustomCodeRequest> representing the request to sign.
 @param options Options to be applied to the request.
 
 @return A signed request to be placed on an operation queue.
 */
- (NSMutableURLRequest *)customCodeRequest:(SMCustomCodeRequest *)request options:(SMRequestOptions *)options;

/**
 Sets the Authorization header of the request using the client's credentials and a MAC header algorithm.
 
 @param request An instance of `NSMutableURLRequest` to be signed with this client's credentials.
 */
- (void)signRequest:(NSMutableURLRequest *)request;

/**
 Returns whether the client has non-nil values for both the accesToken and macKey.
 
 @return `YES` is the credentials are valid, otherwise `NO`.
 */
- (BOOL)hasValidCredentials;

/**
 Return the port that the host is connected to.
 
 @return The port that is being connected to.
 */
- (NSString *)getPort;

/**
 Creates the MAC header for OAuth2 authorization.
 
 The current timestamp and a random nonce are used.
 
 @param method The HTTP verb to use, either `POST`,`GET`, `PUT`, or `DELETE`.
 @param path The REST path.
 
 @return A string that is set in signRequest: for the Authorization header.
 */
- (NSString *)createMACHeaderForHttpMethod:(NSString *)method path:(NSString *)path;

/**
 Creates the MAC header for OAuth2 authorization.
 
 @param method The HTTP verb to use, either `POST`,`GET`, `PUT`, or `DELETE`.
 @param path The REST path.
 @param timestamp The timestamp to use for the authorization.
 @param nonce The nonce to use for the authorization.
 
 @return A string that is set in <signRequest:> for the Authorization header.
 */
- (NSString *)createMACHeaderForHttpMethod:(NSString *)method path:(NSString *)path timestamp:(double)timestamp nonce:(NSString *)nonce;

@end
