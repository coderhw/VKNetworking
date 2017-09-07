//
//  VKDBBookQueryRequest.m
//  testNetworkingDemo
//
//  Created by vanke on 2017/9/6.
//  Copyright © 2017年 Evan. All rights reserved.
//

#import "VKDBBookQueryRequest.h"

@implementation VKDBBookQueryRequest

- (NSString *)baseUrl {
    return @"https://api.douban.com";
}

- (NSString *)requestUrl {
    return @"v2/book/1220562";
}

- (NSInteger)cacheTimeInSeconds {
    return 3600;
}

- (BOOL)ignoreCache {
    return YES;
}

//- (VKRequestMethod)requestMethod {
//    return VKRequestMethodGET;
//}
//
//- (VKRequestSerializerType)requestSerializerType {
//    return VKRequestSerializerTypeHTTP;
//}
//
//- (VKResponseSerializerType)responseSerializerType {
//    return VKResponseSerializerTypeJSON;
//}

@end
