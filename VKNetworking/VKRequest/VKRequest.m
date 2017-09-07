//
//  VKRequest.m
//  MeiFang
//
//  Created by Zengkaisheng on 2017/3/1.
//  Copyright © 2017年 Vanke.com All rights reserved.
//

#import "VKRequest.h"
#import <MJExtension/MJExtension.h>

static NSString *const head = @"head";
static NSString *const body = @"body";


@implementation VKRequest

- (instancetype)init
{
    self = [super init];
    if (self) {
        _headModel = [[VKHeadModel alloc] init];
    }
    return self;
}

- (instancetype)initWithBodyModel:(VKRequestRootModel *)body
{
    self = [super init];
    if (self) {
        _headModel = [[VKHeadModel alloc] init];
        _bodyModel = body;
    }
    return self;
}

- (NSDictionary *)generateBody
{
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
    if (_headModel) {
        [dic setObject:[[_headModel mj_keyValues] copy] forKey:head];
    }
    
    if (_bodyModel) {
        [dic setObject:[[_bodyModel mj_keyValues] copy] forKey:body];
        
    }
    return dic;

}

/**
 Get 请求

 @param success 成功回调
 @param failure 失败回调
 */
- (void)startRequestWithGet:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure{
    
    self.netManager = [[VKNetworkingManager alloc] initWithUrl:_url];
    NSDictionary *items = [self generateBody];
    if(self.isMock){
        NSDictionary *result =  [self mockResponseDicFromMethod:self.url];
        success(result);
    
    }else{
        
        [self.netManager getRequestWithParameters:items withBlock:^(NSDictionary *result, NSDictionary *errInfo) {
            
            if(result) {
                if (success) {
//                    success(result);
                    success(result[@"body"]);
                }
            }else {
                
                if([errInfo isKindOfClass:[NSDictionary class]]) {
                    
                    //更新Token
                    NSString *errCode = errInfo[VKMCResultErrorCodeKey];
                    if([errCode integerValue] == VKRequest_accessTokenExpire){
                        
                        [self refreshTokenResult:^(NSDictionary *result, NSDictionary *errInfo) {
                            
                            if(result && [result isKindOfClass:[NSDictionary class]]){
                                NSDictionary *body = result[VKMCResultBodyKey];
                                NSDictionary *state = result[VKMCResultStateKey];
                                NSString *errCode = state[VKMCResultErrorCodeKey];
                                if([errCode integerValue] == VKRequest_success) {
                                    
//                                    APPContext.user.refreshToken = body[@"refreshToken"];
//                                    APPContext.user.accessToken = body[@"accessToken"];
                                    //递归
                                    [self startRequestWithGet:success withFailed:failure];
                                }else{
                                    //更新失败跳转至登录界面
//                                    [[NSNotificationCenter defaultCenter] postNotificationName:kNotification_refreshTokenExpire
//                                                                                        object:nil];
                                }
                            }
                        }];
                    }else{
                        //其它错误
                        if (errInfo) {
                            if (failure) {
                                NSString *errorMsg = [NSString stringWithFormat:@"%@", errInfo[VKMCResultErrorKey]];
                                failure(errorMsg?errorMsg:kServerErrorMsg);
                            }
                        }
                    }
                }
            }
        }];
    }
}

/**
 POST

 @param success 成功回调
 @param failure 失败回调
 */
- (void)startRequest:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure
{
    //在这个方法中刷新Token
    self.netManager = [[VKNetworkingManager alloc] initWithUrl:_url];
    NSDictionary *items = [self generateBody];
    //在这里判断是否是网络请求还是Mock数据
    if(self.isMock){
        NSDictionary *result =  [self mockResponseDicFromMethod:self.url];
        success(result);

    }else{
        [self.netManager postRequestWithParameters:items withBlock:^(NSDictionary *result, NSDictionary *errInfo) {
            if (result) {
                if (success) {
//                    success(result);
                    success(result[@"body"]);
                }
            }else {
                if([errInfo isKindOfClass:[NSDictionary class]]){
                    //更新Token
                    NSString *errCode = errInfo[VKMCResultErrorCodeKey];
                    if([errCode integerValue] == VKRequest_accessTokenExpire){
                        
                        [self refreshTokenResult:^(NSDictionary *result, NSDictionary *errInfo) {
                            
                            if(result && [result isKindOfClass:[NSDictionary class]]){
                                NSDictionary *body = result[VKMCResultBodyKey];
                                NSDictionary *state = result[VKMCResultStateKey];
                                NSString *errCode = state[VKMCResultErrorCodeKey];
                                if([errCode integerValue] == VKRequest_success) {
                                    
//                                    APPContext.user.refreshToken = body[@"refreshToken"];
//                                    APPContext.user.accessToken = body[@"accessToken"];
                                    [self startRequest:success withFailed:failure];//递归
                                }else{
                                    //更新失败跳转至登录界面
//                                    [[NSNotificationCenter defaultCenter] postNotificationName:kNotification_refreshTokenExpire
//                                                                                        object:nil];
                                }
                            }
                        }];
                    }else{
                        //其它错误
                        if (errInfo) {
                            if (failure) {
                                NSString *errorMsg = [NSString stringWithFormat:@"%@", errInfo[VKMCResultErrorKey]];
                                failure(errorMsg?errorMsg:kServerErrorMsg);
                            }
                        }
                    }
                }
            }
        }];
    }
}

/**
 PUT 请求

 @param success
 @param failure
 */
- (void)startRequestWithPUT:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure {
   
    self.netManager = [[VKNetworkingManager alloc] initWithUrl:_url];
    NSDictionary *items = [self generateBody];
    //在这里判断是否是网络请求还是Mock数据
    if(self.isMock){
        NSDictionary *result =  [self mockResponseDicFromMethod:self.url];
        success(result);
        
    }else{
        [self.netManager putRequestWithParameters:items
                                        withBlock:^(NSDictionary *result, NSDictionary *errInfo) {
            if (result) {
                if (success) {
//                    success(result);
                    success(result[@"body"]);
                }
            }
            else {
                if([errInfo isKindOfClass:[NSDictionary class]]){
                    //更新Token
                    NSString *errCode = errInfo[VKMCResultErrorCodeKey];
                    if([errCode integerValue] == VKRequest_accessTokenExpire){
                        
                        [self refreshTokenResult:^(NSDictionary *result, NSDictionary *errInfo) {
                            
                            if(result && [result isKindOfClass:[NSDictionary class]]){
                                NSDictionary *body = result[VKMCResultBodyKey];
                                NSDictionary *state = result[VKMCResultStateKey];
                                NSString *errCode = state[VKMCResultErrorCodeKey];
                                if([errCode integerValue] == VKRequest_success) {
                                    
//                                    APPContext.user.refreshToken = body[@"refreshToken"];
//                                    APPContext.user.accessToken = body[@"accessToken"];
                                    //递归
                                    [self startRequestWithPUT:success withFailed:failure];
                                }else{
                                    //更新失败跳转至登录界面
//                                    [[NSNotificationCenter defaultCenter] postNotificationName:kNotification_refreshTokenExpire
//                                                                                        object:nil];
                                }
                            }
                        }];
                    }else{
                        //其它错误
                        if (errInfo) {
                            if (failure) {
                                NSString *errorMsg = [NSString stringWithFormat:@"%@", errInfo[VKMCResultErrorKey]];
                                failure(errorMsg?errorMsg:kServerErrorMsg);
                            }
                        }
                    }
                }
            }
        }];
    }
}


/**
 DELETE 请求
 
 @param success
 @param failure
 */
- (void)startRequestWithDelete:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure {
    
    self.netManager = [[VKNetworkingManager alloc] initWithUrl:_url];
    NSDictionary *items = [self generateBody];
    //在这里判断是否是网络请求还是Mock数据

    if(self.isMock){
        NSDictionary *result =  [self mockResponseDicFromMethod:self.url];
        success(result);
        
    }else{
        [self.netManager deleteRequestWithParameters:items
                                           withBlock:^(NSDictionary *result, NSDictionary *errInfo) {
            if (result) {
                if (success) {
//                    success(result);
                    success(result[@"body"]);
                }
            }else{
                
                if([errInfo isKindOfClass:[NSDictionary class]]){
                    
                    //更新Token
                    NSString *errCode = errInfo[VKMCResultErrorCodeKey];
                    if([errCode integerValue] == VKRequest_accessTokenExpire){
                        
                        [self refreshTokenResult:^(NSDictionary *result, NSDictionary *errInfo) {
                            
                            if(result && [result isKindOfClass:[NSDictionary class]]){
                                NSDictionary *body = result[VKMCResultBodyKey];
                                NSDictionary *state = result[VKMCResultStateKey];
                                NSString *errCode = state[VKMCResultErrorCodeKey];
                                if([errCode integerValue] == VKRequest_success) {
                                    
//                                    APPContext.user.refreshToken = body[@"refreshToken"];
//                                    APPContext.user.accessToken = body[@"accessToken"];
                                    //递归
                                    [self startRequestWithDelete:success withFailed:failure];
                                }else{
                                    //更新失败跳转至登录界面
//                                    [[NSNotificationCenter defaultCenter] postNotificationName:kNotification_refreshTokenExpire
//                                                                                        object:nil];
                                }
                            }
                        }];
                    }else{
                        //其它错误
                        if (errInfo) {
                            if (failure) {
                                NSString *errorMsg = [NSString stringWithFormat:@"%@", errInfo[VKMCResultErrorKey]];
                                failure(errorMsg?errorMsg:kServerErrorMsg);
                            }
                        }
                    }
                }
            }
        }];
    }
}

#pragma mark - RACSignal
- (RACSignal *)signal {
    RACSignal *signal = [RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {

        self.netManager = [[VKNetworkingManager alloc] initWithUrl:_url];
        NSDictionary *items = [self generateBody];
        //在这里判断是否是网络请求还是Mock数据
        
        if(self.isMock){
            NSDictionary *result =  [self mockResponseDicFromMethod:self.url];
            // succ
            [subscriber sendNext:result];
            [subscriber sendCompleted];
            
        }else{
            [self.netManager postRequestWithParameters:items withBlock:^(NSDictionary *result, NSDictionary *errInfo) {
                if (result) {
                    // succ
                    [subscriber sendNext:result];
                    [subscriber sendCompleted];
                }
                else {
                    if (errInfo) {
                        NSError *error = [NSError errorWithDomain:@"error" code:90006 userInfo:errInfo];
                        [subscriber sendError:error];

                    }
                }
            }];
        }
        
        return [RACDisposable disposableWithBlock:^{
        }];
       
    }];
    return signal;
}


//构建mock数据
- (NSDictionary *)mockResponseDicFromMethod:(NSString *)method {
    // TODO: build mock response
    NSString *filePath = [method stringByReplacingOccurrencesOfString:@"/"
                                      withString:@""
                                         options:NSCaseInsensitiveSearch
                                           range:NSMakeRange(0, method.length)];
    NSString *jsonPath = [[NSBundle mainBundle] pathForResource:filePath ofType:@"do"];
    
    if (jsonPath) {
        NSData *jsonData = [[NSData alloc] initWithContentsOfFile:jsonPath];
        if (jsonData) {
            NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            NSDictionary *result = [self dictionaryWithJsonString:jsonString];
            if (jsonString) {
                return result;
            }
            else {
                NSLog(@"json parse error");
            }
        }
        else {
            NSLog(@"json data error");
        }
    }
    else {
        NSLog(@"jsonpath = nil");
    }
    return nil;
}


/**
 Token刷新接口
 @param success 成功回调
 */
- (void)refreshTokenResult:(void (^)(NSDictionary *result, NSDictionary *errInfo))success {
    
//    //在这个方法中刷新Token
//    NSString *method = @"userSvc/refresh";
//    self.netManager = [[VKNetworkingManager alloc] initWithUrl:method];
//    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
//    NSMutableDictionary *bodyDic = [NSMutableDictionary dictionary];
//    if (_headModel) {
//        [dic setObject:[[_headModel mj_keyValues] copy] forKey:head];
//    }
//    [bodyDic setObject:APPContext.user.ID forKey:@"userid"];
//    [bodyDic setObject:APPContext.user.refreshToken forKey:@"refreshtoken"];
//    [dic setObject:bodyDic forKey:body];
//    
//    [self.netManager postRequestWithParameters:dic withBlock:^(NSDictionary *result, NSDictionary *errInfo) {
//        success(result, errInfo);
//    }];
    
}

#pragma mark - Private
- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString
    {
        if (jsonString == nil) {
            return nil;
        }
        
        NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                            options:NSJSONReadingMutableContainers
                                                              error:&err];
        if(err)
        {
            NSLog(@"json解析失败：%@",err);
            return nil;
        }
        return dic;
}

@end
