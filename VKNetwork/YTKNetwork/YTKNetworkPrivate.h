//
//  YTKNetworkPrivate.h
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "YTKRequest.h"
#import "YTKBaseRequest.h"
//#import "YTKBatchRequest.h"
//#import "YTKChainRequest.h"
#import "YTKNetworkAgent.h"
#import "YTKNetworkConfig.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT void YTKLog(NSString *format, ...) NS_FORMAT_FUNCTION(1,2);

@class AFHTTPSessionManager;

@interface YTKNetworkUtils : NSObject

+ (BOOL)validateJSON:(id)json withValidator:(id)jsonValidator;

+ (void)addDoNotBackupAttribute:(NSString *)path;

+ (NSString *)md5StringFromString:(NSString *)string;

+ (NSString *)appVersionString;

+ (NSStringEncoding)stringEncodingWithRequest:(YTKBaseRequest *)request;

+ (BOOL)validateResumeData:(NSData *)data;

@end

@interface YTKRequest (Getter)

- (NSString *)cacheBasePath;

@end

@interface YTKBaseRequest (Setter)

@property (nonatomic, strong, readwrite) NSURLSessionTask *requestTask;
@property (nonatomic, strong, readwrite, nullable) NSData *responseData;
@property (nonatomic, strong, readwrite, nullable) id responseJSONObject;
@property (nonatomic, strong, readwrite, nullable) id responseObject;
@property (nonatomic, strong, readwrite, nullable) NSString *responseString;
@property (nonatomic, strong, readwrite, nullable) NSError *error;

@end

@interface YTKBaseRequest (RequestAccessory)

- (void)toggleAccessoriesWillStartCallBack;
- (void)toggleAccessoriesWillStopCallBack;
- (void)toggleAccessoriesDidStopCallBack;

@end

@interface YTKNetworkAgent (Private)

- (AFHTTPSessionManager *)manager;
- (void)resetURLSessionManager;
- (void)resetURLSessionManagerWithConfiguration:(NSURLSessionConfiguration *)configuration;

- (NSString *)incompleteDownloadTempCacheFolder;

@end

NS_ASSUME_NONNULL_END

