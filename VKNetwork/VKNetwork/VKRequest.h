//
//  VKRequest.h
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//


#import "VKBaseRequest.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const VKRequestCacheErrorDomain;

NS_ENUM(NSInteger) {
    VKRequestCacheErrorExpired = -1,
    VKRequestCacheErrorVersionMismatch = -2,
    VKRequestCacheErrorSensitiveDataMismatch = -3,
    VKRequestCacheErrorAppVersionMismatch = -4,
    VKRequestCacheErrorInvalidCacheTime = -5,
    VKRequestCacheErrorInvalidMetadata = -6,
    VKRequestCacheErrorInvalidCacheData = -7,
};

///  VKRequest is the base class you should inherit to create your own request class.
///  Based on VKBaseRequest, VKRequest adds local caching feature. Note download
///  request will not be cached whatsoever, because download request may involve complicated
///  cache control policy controlled by `Cache-Control`, `Last-Modified`, etc.
/// VKRequest
@interface VKRequest : VKBaseRequest

///  是否使用缓存
///  默认为No, 需要配置额外的参数才能让缓存发挥作用。
///  注意'cacheTimeInSeconds'
///  事实上，如果不给cacheTimeInSeconds设置一个有效值，那么将不会有作用
///  该值不会影响即将缓存的响应数据。意味着:响应数据每次都会被缓存下来。即使ignoreCache为YES
@property (nonatomic) BOOL ignoreCache;

/// 当前的数据是否从缓存获得
- (BOOL)isDataFromCache;

///  是否成功从缓存中读取数据
///
///  @param error 如果过程中出现错误，将会传递error对象，否则为NULL
///
///  @return BOOL值 是否成功从缓存中读取数据
- (BOOL)loadCacheWithError:(NSError * __autoreleasing *)error;

///  强制更新缓存
- (void)startWithoutCache;

///  Save response data (probably from another request) to this request's cache location
- (void)saveResponseDataToCacheFile:(NSData *)data;

#pragma mark - Subclass Override

///  缓存的时间. (默认为-1. 实际上缓存并没有保存起来)
- (NSInteger)cacheTimeInSeconds;

///  cacheVersion:可以用来鉴定和是本地的的cache失效，默认值为0
- (long long)cacheVersion;

///  This can be used as additional identifier that tells the cache needs updating.
///
///  @discussion The `description` string of this object will be used as an identifier to verify whether cache
///              is invalid. Using `NSArray` or `NSDictionary` as return value type is recommended. However,
///              If you intend to use your custom class type, make sure that `description` is correctly implemented.
- (nullable id)cacheSensitiveData;

///  cache是否是异步写入缓存，默认为YES
- (BOOL)writeCacheAsynchronously;

@end

NS_ASSUME_NONNULL_END
