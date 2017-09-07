//
//  VKNetworkingManager.h
//  MeiFang
//
//  Created by Zengkaisheng on 2017/3/1.
//  Copyright © 2017年 Vanke.com All rights reserved.
//

//#import "VKObject.h"
#import <AFNetworking/AFNetworking.h>
#import "VKRequestHeader.h"

#define kNetworkErrorMsg    @"网络异常，请稍后再试"
#define kServerErrorMsg     @"服务异常，请稍后再试"
#define kTokenErrorMsg      @"安全验证失败，请重新登录"
#define kTimerOut           30

/**
 *  回调结果
 *
 *  @param result  请求信息
 *  @param errInfo 错误信息
 */
typedef void(^VKNetResult)(NSDictionary *result,NSDictionary *errInfo);

typedef NS_ENUM(NSInteger, VKRequestErrorCode) {
    VKRequest_success = 10000,
    VKRequest_versionState = 800001,
    VKRequest_accessTokenExpire  = 10002, //accessToken 过期
    VKRequest_refreshTokenInvalid = 10022,  //refreshToken 过期
};

/**
 网络请求框架
 */
@interface VKNetworkingManager : NSObject

/**
 *  初始化
 *
 *  @param url 请求地址
 *
 *  @return VKNetworkingManager 对象
 */
- (instancetype)initWithUrl:(NSString *)url;

@property (nonatomic, copy, readonly) NSString *url;
@property (nonatomic, assign, readonly) VKRequestErrorCode errCode;

/**
 *  get请求
 *
 *  @param items   参数
 *  @param results 回调
 *
 */
- (void)getRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results;
/**
 *  post请求
 *
 *  @param items   参数
 *  @param results 回调
 *
 */
- (void)postRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results;

/**
 PUT请求

 @param items 参数
 @param results 回调
 */
- (void)putRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results;


/**
 DELETE 请求
 
 @param items 参数
 @param results 回调
 */
- (void)deleteRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results;


/**
 *  全部开启
 */
- (void)allStart;

/**
 *  全部暂停
 */
- (void)allPause;

@end

FOUNDATION_EXPORT NSString *const VKMCResultBodyKey;
FOUNDATION_EXPORT NSString *const VKMCResultStateKey;
FOUNDATION_EXPORT NSString *const VKMCResultErrorKey;
FOUNDATION_EXPORT NSString *const VKMCResultMessageKey;
FOUNDATION_EXPORT NSString *const VKMCResultErrorCodeKey;
FOUNDATION_EXPORT NSString *const VKMCResultDownloadPathKey;
FOUNDATION_EXPORT NSString *const VKMCResultInfoKey;
