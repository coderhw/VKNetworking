//
//  VKNetworkConfig.h
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class VKBaseRequest;
@class AFSecurityPolicy;

///  VKUrlFilterProtocol 可以通过它给请求追加参数
@protocol VKUrlFilterProtocol <NSObject>

///  在请求发出去之前预处理Request URL
///
///  @param originUrl request's origin URL, which is returned by `requestUrl`
///  @param request   request itself
///
///  @return A new url which will be used as a new `requestUrl`
- (NSString *)filterUrl:(NSString *)originUrl withRequest:(VKBaseRequest *)request;

@end

///  VKCacheDirPathFilterProtocol can be used to append common path components when caching response results
@protocol VKCacheDirPathFilterProtocol <NSObject>

///  在保存之前提前配置cache path
///
///  @param originPath original base cache path, which is generated in `VKRequest` class.
///  @param request    request itself
///
///  @return A new path which will be used as base path when caching.
- (NSString *)filterCacheDirPath:(NSString *)originPath withRequest:(VKBaseRequest *)request;
@end

///  VKNetworkConfig 保存了全局的network相关的配置参数,
///  这些参数将会用在VKNetworkAgent中去实现request或者filter Request, 或者caching response
@interface VKNetworkConfig : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

///  返回config object
+ (VKNetworkConfig *)sharedConfig;

///  请求Host, eg:http://www.vanke.com 默认为nil
@property (nonatomic, strong) NSString *baseUrl;

///  请求的CDN URL, 默认为nil
@property (nonatomic, strong) NSString *cdnUrl;

///  URL filters. See also `VKUrlFilterProtocol`.
@property (nonatomic, strong, readonly) NSArray<id<VKUrlFilterProtocol>> *urlFilters;

///  Cache path filters. See also `VKCacheDirPathFilterProtocol`.
@property (nonatomic, strong, readonly) NSArray<id<VKCacheDirPathFilterProtocol>> *cacheDirPathFilters;

///  Security policy,将会被AFNetworking使用 See also `AFSecurityPolicy`.
@property (nonatomic, strong) AFSecurityPolicy *securityPolicy;

///  是否记录debug信息, 默认为YES
@property (nonatomic) BOOL debugLogEnabled;

///  SessionConfiguration将会被用来初始化AFHTTPSessionManager, 默认为nil
@property (nonatomic, strong) NSURLSessionConfiguration* sessionConfiguration;

///  添加url filter.
- (void)addUrlFilter:(id<VKUrlFilterProtocol>)filter;

///  移除所有URL filters
- (void)clearUrlFilter;

///  添加cache path filter
- (void)addCacheDirPathFilter:(id<VKCacheDirPathFilterProtocol>)filter;

///  移除所有 cache path filters.
- (void)clearCacheDirPathFilter;

@end

NS_ASSUME_NONNULL_END
