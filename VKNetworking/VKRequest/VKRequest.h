//
//  VKRequest.h
//  MeiFang
//
//  Created by Zengkaisheng on 2017/3/1.
//  Copyright © 2017年 Vanke.com All rights reserved.
//

//#import "VKObject.h"
#import "VKNetworkingManager.h"
#import "VKHeadModel.h"
#import <ReactiveCocoa.h>

typedef void(^VKRequestSuccessBlock) (id info);
typedef void(^VKRequestFailBlock) (NSString *errMsg);

@interface VKRequest : NSObject

@property (nonatomic, strong) VKHeadModel *headModel;
@property (nonatomic, strong) VKRequestRootModel *bodyModel;
@property (nonatomic, copy) NSString *url;
@property (nonatomic, strong) VKNetworkingManager *netManager;
@property (nonatomic, assign) BOOL isMock;


- (NSDictionary *)generateBody;

- (instancetype)initWithBodyModel:(VKRequestRootModel *)body;

/**
 Get方式请求

 @param success 成功回调
 @param failure 失败回调
 */
- (void)startRequestWithGet:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure;

/**
 Post方式请求
 
 @param success 成功回调
 @param failure 失败回调
 */
- (void)startRequest:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure;

/**
 Put方式请求
 
 @param success 成功回调
 @param failure 失败回调
 */
- (void)startRequestWithPUT:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure;

/**
 Delete方式请求
 
 @param success 成功回调
 @param failure 失败回调
 */
- (void)startRequestWithDelete:(VKRequestSuccessBlock)success withFailed:(VKRequestFailBlock)failure;


/**
 信号

 @return 需要订阅该信号
 */
- (RACSignal *)signal;

@end
