//
//  VKNetworkingManager.m
//  MeiFang
//
//  Created by Zengkaisheng on 2017/3/1.
//  Copyright © 2017年 Vanke.com All rights reserved.
//

#import "VKNetConstant.h"
#import "VKNetworkingManager.h"

/**
 *将AFURLSessionManager类的实例改成单例模式，解决AFNetworking 3的内存泄漏问题
 */
static AFURLSessionManager *_urlsessionManager = nil;

@interface VKNetworkingManager ()
{
    NSMutableDictionary *dic;
    NSMutableSet *tasks;
}

@end

@implementation VKNetworkingManager

- (instancetype)initWithUrl:(NSString *)url {
    self = [super init];
    if (self) {
        
        dic = [NSMutableDictionary dictionary];
        [self setupUrl:url];
        tasks = [NSMutableSet set];
    }
    return self;
}

#pragma mark -
#pragma mark -获得单例方法
- (AFURLSessionManager *)sharedUrlSessionManager
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _urlsessionManager = [[AFURLSessionManager alloc] initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    });
    
    return _urlsessionManager;
}

- (void)setupSuccessBlock:(VKNetResult)results withIfo:(NSDictionary *)response {
    
    //处理后台数据返回异常错误
    id body = [response objectForKey:@"body"];
    id state = [response objectForKey:@"state"];
    if(![body isKindOfClass:[NSDictionary class]] || ![state isKindOfClass:[NSDictionary class]] ){
        results(nil, @{VKMCResultErrorKey:kServerErrorMsg});
        return;
    }
    
    if (results && response) {
        
        _errCode = [response[VKMCResultStateKey][VKMCResultErrorCodeKey] integerValue];
        if (_errCode == VKRequest_success) {
            results(response,nil);
            
        }else if (_errCode == VKRequest_versionState) {
            
            results(nil, response);
        }else {
            //refreshToken失效 跳转至登录页面
            if(_errCode == VKRequest_refreshTokenInvalid){
//                [[NSNotificationCenter defaultCenter] postNotificationName:kNotification_refreshTokenExpire
//                                                                    object:nil];
            }
            //accessToken失效 刷新token
            if(_errCode == VKRequest_accessTokenExpire){
                results(nil, @{VKMCResultErrorCodeKey:@(VKRequest_accessTokenExpire)});
            }
            
            NSString *errMsg = nil;
            //这里的错误信息，优先去body里面的信息，再去state里面的信息
            if([response isKindOfClass:[NSDictionary class]]){
                
                id body = response[VKMCResultBodyKey];
                //避免body有时候直接是字符串返回导致crash
                if([body isKindOfClass:[NSDictionary class]]) {
                    //取errMeg
                    errMsg = response[VKMCResultBodyKey][VKMCResultErrorKey];
                    //取message
                    if(!errMsg || !errMsg.length){
                        errMsg = response[VKMCResultBodyKey][VKMCResultMessageKey];
                    }
                }else if ([body isKindOfClass:[NSString class]]){
                    errMsg = body;
                }
                
                //state
                if(!errMsg.length || !errMsg){
                    errMsg = response[VKMCResultStateKey][VKMCResultErrorKey];
                }
            }
            
            if (errMsg) {
            
                results(nil,@{VKMCResultErrorKey:errMsg});
            }else{
                if([response respondsToSelector:@selector(objectForKey:)]){
                    NSString *stateCode = [response objectForKey:@"code"];
                    if([stateCode integerValue] != VKRequest_success){
                        results(nil,@{VKMCResultErrorKey:kServerErrorMsg});
                    }
                }
            }
        }
    }
}

- (void)setupFailureBlock:(VKNetResult)results withErrorMessage:(NSString *)msg {
    
    if (results && msg) {
        results(nil,@{VKMCResultErrorKey:msg});
    }
}

/**
 Get

 @param items 参数
 @param results 回调
 */
- (void)getRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results {
    NSString *json = [self convertToJSONData:items];

    if(!_url) return;
    [self setupParameters:items];
    //AFURLSessionManager *sessionManager = [[AFURLSessionManager alloc] initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    NSMutableURLRequest *request = [self requestWithParameters:dic url:_url method:@"GET"];
    request.timeoutInterval = kTimerOut;
    [[[self sharedUrlSessionManager] dataTaskWithRequest:request completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        if(!error) {
            
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            NSDictionary *tempResponse = responseObject;
            if([responseObject isKindOfClass:[NSData class]]){
                tempResponse = [NSJSONSerialization JSONObjectWithData:responseObject options:NSJSONReadingMutableContainers error:nil];
            }
            
            [self setupSuccessBlock:results withIfo:tempResponse];
        }else{
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            [self setupFailureBlock:results withErrorMessage:kServerErrorMsg];
        }
    }] resume];

}


/**
 Post

 @param items 参数
 @param results 回调
 */
- (void)postRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results {
    
    NSString *json = [self convertToJSONData:items];
    
    if(!_url) return;
    [self setupParameters:items];
    //AFURLSessionManager *sessionManager = [[AFURLSessionManager alloc] initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    NSMutableURLRequest *request = [self requestWithParameters:dic url:_url method:@"POST"];
    request.timeoutInterval = kTimerOut;
    [[[self sharedUrlSessionManager] dataTaskWithRequest:request completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        if(!error){
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            NSDictionary *tempResponse = responseObject;
            if([responseObject isKindOfClass:[NSData class]]){
                tempResponse = [NSJSONSerialization JSONObjectWithData:responseObject options:NSJSONReadingMutableContainers error:nil];
            }
            [self setupSuccessBlock:results withIfo:tempResponse];
            
        }else{
            
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            [self setupFailureBlock:results withErrorMessage:kServerErrorMsg];
        }
    }] resume];

}

/**
 Put
 @param items 参数
 @param results 回调
 */
- (void)putRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results {
    NSString *json = [self convertToJSONData:items];

    
    if(!_url) return;
    [self setupParameters:items];
    
    //AFURLSessionManager *sessionManager = [[AFURLSessionManager alloc] initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    NSMutableURLRequest *request = [self requestWithParameters:dic url:_url method:@"PUT"];
    request.timeoutInterval = kTimerOut;
    [[[self sharedUrlSessionManager] dataTaskWithRequest:request completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        if (!error) {
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            NSDictionary *tempResponse = responseObject;
            if([responseObject isKindOfClass:[NSData class]]){
                tempResponse = [NSJSONSerialization JSONObjectWithData:responseObject options:NSJSONReadingMutableContainers error:nil];
            }
            [self setupSuccessBlock:results withIfo:tempResponse];
        } else {
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            [self setupFailureBlock:results withErrorMessage:kServerErrorMsg];
        }
    }] resume];
}
/**
 Delete
 @param items 参数
 @param results 回调
 */
- (void)deleteRequestWithParameters:(NSDictionary *)items withBlock:(VKNetResult)results {
    
    NSString *json = [self convertToJSONData:items];

    if(!_url) return;
    [self setupParameters:items];
    //AFURLSessionManager *sessionManager = [[AFURLSessionManager alloc] initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    NSMutableURLRequest *request = [self requestWithParameters:dic url:_url method:@"DELETE"];
    request.timeoutInterval = kTimerOut;
    [[[self sharedUrlSessionManager] dataTaskWithRequest:request completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        if (!error) {
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            NSDictionary *tempResponse = responseObject;
            if([responseObject isKindOfClass:[NSData class]]){
                tempResponse = [NSJSONSerialization JSONObjectWithData:responseObject options:NSJSONReadingMutableContainers error:nil];
            }
            [self setupSuccessBlock:results withIfo:tempResponse];
        } else {
            NSLog(@"--Pramas:%@\n--URL:%@\n--Respone:%@", json, _url, responseObject);
            [self setupFailureBlock:results withErrorMessage:kServerErrorMsg];
        }
    }] resume];
    
}

- (void)allStart {
    
    for (NSURLSessionTask *task in tasks) {
        [task resume];
    }
}
- (void)allPause {
    for (NSURLSessionTask *task in tasks) {
        [task suspend];
    }
}
#pragma mark - Private Methods
- (void)setupParameters:(NSDictionary *)items {
    if(items){        
        [dic addEntriesFromDictionary:items];
    }
}

/**
 设置Request Header & Body

 @param parameters 参数
 @param method 请求方法 Get/Post/Put/Delete
 @return Request
 */
- (NSMutableURLRequest *)requestWithParameters:(NSDictionary *)parameters
                                           url:(NSString *)url
                                        method:(NSString *)method {
    
    //定制化GET请求 eg: http:..../id
    NSMutableString *tempURL = [[NSMutableString alloc] initWithString:url];
    if([method isEqualToString:@"GET"]||[method isEqualToString:@"DELETE"]) {
        
        if([dic.allKeys containsObject:@"body"]){
            NSDictionary *bodyInfo = dic[@"body"];
            if([bodyInfo.allKeys containsObject:@"id"]){
                NSString *idStr = [bodyInfo objectForKey:@"id"];
                [tempURL appendFormat:@"/%@", idStr];
            }
        }
        NSLog(@"tempURL:%@", tempURL);

        NSMutableURLRequest *request =  [[AFJSONRequestSerializer serializer]
                                         requestWithMethod:method URLString:tempURL parameters:nil error:nil];
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
        [request setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        if([dic.allKeys containsObject:@"head"]){
            NSDictionary *headInfo = dic[@"head"];
            for (NSString *key in headInfo.allKeys) {
                NSString *value = [headInfo objectForKey:key];
                if([value isKindOfClass:[NSString class]]){
                    if(value.length){
                        [request setValue:value forHTTPHeaderField:key];
                    }
                }
            }
        }
        return request;
        
    }else{
        
        NSMutableURLRequest *request =  [[AFJSONRequestSerializer serializer]
                                         requestWithMethod:method URLString:url parameters:nil error:nil];
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
        [request setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        if([dic.allKeys containsObject:@"head"]){
            NSDictionary *headInfo = dic[@"head"];
            for (NSString *key in headInfo.allKeys) {
                NSString *value = [headInfo objectForKey:key];
                if([value isKindOfClass:[NSString class]]){
                    if(value.length){
                        [request setValue:value forHTTPHeaderField:key];
                    }
                }
            }
        }
        if([dic.allKeys containsObject:@"body"]){
            NSDictionary *bodyInfo = dic[@"body"];
            NSError *error;
            NSData *jsonData = [NSJSONSerialization dataWithJSONObject:bodyInfo options:0 error:&error];
            if(!error){
                NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
                [request setHTTPBody:[jsonString dataUsingEncoding:NSUTF8StringEncoding]];
            }else{
                NSLog(@"JSONSerialization Failed:%@", [error localizedDescription]);
            }
        }
        return request;
    }
    
}

-(void)setupUrl:(NSString *)url {
    
    if(VKNetworkHost.length) {
        _url = [VKNetworkHost stringByAppendingFormat:@"/%@", url];
    }else{
        _url = url;
    }
}
    
- (NSString*)convertToJSONData:(id)infoDict {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:infoDict
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    NSString *jsonString = @"";
    
    if (!jsonData){
        
        NSLog(@"Got an error: %@", error);
    }else{
        
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    //去除掉首尾的空白字符和换行字符
    jsonString = [jsonString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    [jsonString stringByReplacingOccurrencesOfString:@"\n" withString:@""];
    
    return jsonString;
}


@end
NSString *const VKMCResultBodyKey = @"body";
NSString *const VKMCResultStateKey = @"state";
NSString *const VKMCResultErrorKey = @"errMsg";
NSString *const VKMCResultMessageKey = @"message";
NSString *const VKMCResultErrorCodeKey = @"errCode";
NSString *const VKMCResultDownloadPathKey = @"com.path.download.vanke";
NSString *const VKMCResultInfoKey = @"info";
