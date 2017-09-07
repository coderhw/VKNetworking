//
//  VKNetworkAgent.h
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class VKBaseRequest;

///  VKNetworkAgent is the underlying class that handles actual request generation,
///  serialization and response handling.
@interface VKNetworkAgent : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

///  获取Agent单例
+ (VKNetworkAgent *)sharedAgent;

/// 将请求加入session中，并发起请求
- (void)addRequest:(VKBaseRequest *)request;

///  取消之前发起的请求
- (void)cancelRequest:(VKBaseRequest *)request;

/// 取消加入请求队列的所有请求
- (void)cancelAllRequests;

///  Return the constructed URL of request.
///
///  @param request The request to parse. Should not be nil.
///
///  @return The result URL.
- (NSString *)buildRequestUrl:(VKBaseRequest *)request;

@end

NS_ASSUME_NONNULL_END
