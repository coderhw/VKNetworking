//
//  YTKBaseRequest.h
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const YTKRequestValidationErrorDomain;

NS_ENUM(NSInteger) {
    YTKRequestValidationErrorInvalidStatusCode = -8,
    YTKRequestValidationErrorInvalidJSONFormat = -9,
};

///  HTTP请求方法
typedef NS_ENUM(NSInteger, YTKRequestMethod) {
    YTKRequestMethodGET = 0,
    YTKRequestMethodPOST,
    YTKRequestMethodHEAD,
    YTKRequestMethodPUT,
    YTKRequestMethodDELETE,
    YTKRequestMethodPATCH,
};

///  Request serializer type.
typedef NS_ENUM(NSInteger, YTKRequestSerializerType) {
    YTKRequestSerializerTypeHTTP = 0,
    YTKRequestSerializerTypeJSON,
};

///  响应部分序列化类型。通过它决定了response serialization process 和 responseObject
typedef NS_ENUM(NSInteger, YTKResponseSerializerType) {
    /// NSData type
    YTKResponseSerializerTypeHTTP,
    /// JSON object type
    YTKResponseSerializerTypeJSON,
    /// NSXMLParser type
    YTKResponseSerializerTypeXMLParser,
};

///  请求优先级
typedef NS_ENUM(NSInteger, YTKRequestPriority) {
    YTKRequestPriorityLow = -4L,
    YTKRequestPriorityDefault = 0,
    YTKRequestPriorityHigh = 4,
};

@protocol AFMultipartFormData;

typedef void (^AFConstructingBlock)(id<AFMultipartFormData> formData);
typedef void (^AFURLSessionTaskProgressBlock)(NSProgress *);

@class YTKBaseRequest;

typedef void(^YTKRequestCompletionBlock)(__kindof YTKBaseRequest *request);

/// YTKRequestDelegate 定义了一些可选择的方法，通过这些方法可以接收到网络相关的消息。
/// 所有的这些方法都会在主线程中调用。
@protocol YTKRequestDelegate <NSObject>

@optional
///  代理方法:请求成功结束
///
///  @param request 对应的请求
- (void)requestFinished:(__kindof YTKBaseRequest *)request;

///  代理方法: 请求失败
///
///  @param request 对应的请求
- (void)requestFailed:(__kindof YTKBaseRequest *)request;

@end

/// Objects可以遵循这YTKRequestAccessory协议，通过该协议定义的方法来追踪Request的状态。所有的方法会在主线程中被调用
@protocol YTKRequestAccessory <NSObject>

@optional

///  告诉accessory对象, 该请求即将开始
///
///  @param request The corresponding request.
- (void)requestWillStart:(id)request;

///  告诉accessory, 请求即将结束，该方法在requestFinished和successCompletionBlock之前调用.
///
///  @param request The corresponding request.
- (void)requestWillStop:(id)request;

///  告诉accessory, 请求已经结束，该方法在requestFinished和successCompletionBlock之后调用.
///
///  @param request The corresponding request.
- (void)requestDidStop:(id)request;

@end

///  YTKBaseRequest 是网络请求的一个抽象类，它为创建新的请求提供了一些属性。 并且它是YTKRequest的基类。
@interface YTKBaseRequest : NSObject

#pragma mark - Request and Response Information

///  一般情况下为nil，在请求开始前，不应该访问该属性。
@property (nonatomic, strong, readonly) NSURLSessionTask *requestTask;

///  直接获取`requestTask.currentRequest
@property (nonatomic, strong, readonly) NSURLRequest *currentRequest;

///  直接获取`requestTask.originalRequest`
@property (nonatomic, strong, readonly) NSURLRequest *originalRequest;

///  直接获取`requestTask.response`.
@property (nonatomic, strong, readonly) NSHTTPURLResponse *response;

///  响应状态码
@property (nonatomic, readonly) NSInteger responseStatusCode;

///  The response header fields.
@property (nonatomic, strong, readonly, nullable) NSDictionary *responseHeaders;

/// 未处理过的响应数据。 如果请求失败可能为nil
@property (nonatomic, strong, readonly, nullable) NSData *responseData;

///  响应的数据的字符串，如果请求失败可能为nil
@property (nonatomic, strong, readonly, nullable) NSString *responseString;

///
///  @discussion 这是已经序列化的对象，具体类型取决于YTKResponseSerializerType，注意:如果请求失败可能为nil
///  如果使用了 `resumableDownloadPath` and DownloadTask, 则是文件存放的路径(NSURL)
@property (nonatomic, strong, readonly, nullable) id responseObject;

/// 如果你用了YTKResponseSerializerTypeJSON，那么通过它可以方便的获取到response object，如果不是则为nil
@property (nonatomic, strong, readonly, nullable) id responseJSONObject;

/// serialization error 或者 网络错误，如果没有错误则为nil
@property (nonatomic, strong, readonly, nullable) NSError *error;

///  请求是否取消的状态
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;

/// 请求执行的状态
@property (nonatomic, readonly, getter=isExecuting) BOOL executing;


#pragma mark - Request Configuration
///=============================================================================
/// @name Request Configuration
///=============================================================================


///  可以标识一个请求，默认为0
@property (nonatomic) NSInteger tag;

///  The userInfo can be used to store additional info about the request. Default is nil.
@property (nonatomic, strong, nullable) NSDictionary *userInfo;

///  请求的代理，如果选择通过block方式，请忽略！
@property (nonatomic, weak, nullable) id<YTKRequestDelegate> delegate;

///  成功的回调。 注意:如果successCompletionBlock不为nil, 那么一定实现了requestFinished的代理方法。两者都会执行, 但是代理的方法先执行。
///  该block将会在主线程中调用
@property (nonatomic, copy, nullable) YTKRequestCompletionBlock successCompletionBlock;

///  失败的回调。 注意:如果successCompletionBlock不为nil, 那么一定实现了requestFailed的代理方法。两者都会执行, 但是代理的方法先执行。
///  该block将会在主线程中调用
@property (nonatomic, copy, nullable) YTKRequestCompletionBlock failureCompletionBlock;

///  用于添加accossories object, 注意:如果通过addAccessory来添加acceesory, 该数组则会自动被创建出来, 默认为nil.
@property (nonatomic, strong, nullable) NSMutableArray<id<YTKRequestAccessory>> *requestAccessories;

///  This can be use to construct HTTP body when needed in POST request. Default is nil.
@property (nonatomic, copy, nullable) AFConstructingBlock constructingBodyBlock;

///  This value is used to perform resumable download request. Default is nil.
///
///  @discussion NSURLSessionDownloadTask is used when this value is not nil.
///              The exist file at the path will be removed before the request starts. If request succeed, file will
///              be saved to this path automatically, otherwise the response will be saved to `responseData`
///              and `responseString`. For this to work, server must support `Range` and response with
///              proper `Last-Modified` and/or `Etag`. See `NSURLSessionDownloadTask` for more detail.
@property (nonatomic, strong, nullable) NSString *resumableDownloadPath;

///  You can use this block to track the download progress. See also `resumableDownloadPath`.
@property (nonatomic, copy, nullable) AFURLSessionTaskProgressBlock resumableDownloadProgressBlock;

///  请求优先级 默认`YTKRequestPriorityDefault`.
@property (nonatomic) YTKRequestPriority requestPriority;

///  设置请求完成回调
- (void)setCompletionBlockWithSuccess:(nullable YTKRequestCompletionBlock)success
                              failure:(nullable YTKRequestCompletionBlock)failure;

///  清理 成功和失败的block
- (void)clearCompletionBlock;

///  Convenience method to add request accessory. See also `requestAccessories`.
- (void)addAccessory:(id<YTKRequestAccessory>)accessory;


#pragma mark - Request Action
///=============================================================================
/// @name Request Action
///=============================================================================

///  Append self to request queue and start the request.
- (void)start;

///  Remove self from request queue and cancel the request.
- (void)stop;

/// 通过此方法快速发起请求，并通过block获取回调数据。
- (void)startWithCompletionBlockWithSuccess:(nullable YTKRequestCompletionBlock)success
                                    failure:(nullable YTKRequestCompletionBlock)failure;


#pragma mark - Subclass Override
///=============================================================================
/// @name Subclass Override
///=============================================================================

///  请求成功的回调 (非主线程)
- (void)requestCompletePreprocessor;

/// 请求成功的回调 主线程
- (void)requestCompleteFilter;

///  `requestCompletePreprocessor`.
/// 请求失败的回调 (非主线程)
- (void)requestFailedPreprocessor;

///  Called on the main thread when request failed.
/// 请求失败的回调 (主线程)
- (void)requestFailedFilter;

/// 请求Host https://www.douban.com
- (NSString *)baseUrl;

/// 请求的URL eg: /bookQuery/123667
- (NSString *)requestUrl;

///  cdnURL (如果有需要)
- (NSString *)cdnUrl;

///  请求超时时间, 默认60s
- (NSTimeInterval)requestTimeoutInterval;

/// 请求的参数列表
- (nullable id)requestArgument;

///  Override this method to filter requests with certain arguments when caching.
- (id)cacheFileNameFilterForRequestArgument:(id)argument;

///  Http请求的方法
- (YTKRequestMethod)requestMethod;

/// 请求的SerializerType
- (YTKRequestSerializerType)requestSerializerType;

///  响应的SerializerType
- (YTKResponseSerializerType)responseSerializerType;

/// 请求的Server用户名和密码 Should be formed as @[@"Username", @"Password"].
- (nullable NSArray<NSString *> *)requestAuthorizationHeaderFieldArray;

///  Additional HTTP request header field.
- (nullable NSDictionary<NSString *, NSString *> *)requestHeaderFieldValueDictionary;

/// 构建自定义的UrlRequest，
/// 若这个方法返回非nil对象，会忽略requestUrl, requestTimeoutInterval, requestArgument, allowsCellularAccess
/// requestMethod, requestSerializerType
- (nullable NSURLRequest *)buildCustomUrlRequest;

///  是否使用CDN
- (BOOL)useCDN;

///  是否允许使用蜂窝，默认为YES
- (BOOL)allowsCellularAccess;

///  用于检查JSON是否合法的对象
- (nullable id)jsonValidator;

/// 用于检查Status Code是否正常的方法
- (BOOL)statusCodeValidator;

@end

NS_ASSUME_NONNULL_END
