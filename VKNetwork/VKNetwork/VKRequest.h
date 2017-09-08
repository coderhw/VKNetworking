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


///  VKRequest 是最基础的请求类。所有用户创建的请求必须继承自该类。 VKRequest添加了缓存功能。
///  (注意:如果是下载请求，将不会被缓存下来。)
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


///  cacheSensitiveData可以当做需要更新cache的另外一个标识。
///  该objec的description将会被用来标识cache是否无效。 推荐使用NSArray和NSDictionary作为返回值。
///  但是如果你打算用自定义的class,确保实现了description方法
- (nullable id)cacheSensitiveData;

///  cache是否是异步写入缓存，默认为YES
- (BOOL)writeCacheAsynchronously;

@end

NS_ASSUME_NONNULL_END
