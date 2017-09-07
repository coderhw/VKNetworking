//
//  ViewController.m
//  VKNetwork
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//

#import "ViewController.h"
#import "VKDBBookQueryRequest.h"
#import "VKBaseRequest+AnimatingAccessory.h"


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
}

- (IBAction)getApiRequest:(id)sender {
    
    VKDBBookQueryRequest *dbQueryRequest = [[VKDBBookQueryRequest alloc] init];
    dbQueryRequest.animatingText = @"正在加载";
    dbQueryRequest.animatingView = self.view;
    
    [dbQueryRequest startWithCompletionBlockWithSuccess:^(__kindof VKBaseRequest * _Nonnull request) {
        
        NSLog(@"request:%@", request.responseString);
    } failure:^(__kindof VKBaseRequest * _Nonnull request) {
        
    }];
}



@end
