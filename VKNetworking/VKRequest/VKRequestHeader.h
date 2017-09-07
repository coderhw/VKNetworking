//
//  VKRequestHeader.h
//  ServiceEngineer
//
//  Created by Evan on 16/9/1.
//  Copyright © 2016年 Vanke. All rights reserved.
//

#ifndef VKRequestHeader_h
#define VKRequestHeader_h

#define kVKREQUESTTIMEOUT 30

/**
 *  0   代表http协议
 *  1   代表https协议
 */
#define VKTransferProtocol 0


//static NSString *const VKDBPath = @"serviceengineer.db";

static NSString *const VKGetSysDictURL = @"dictSvc/listBySalesOrgId";   //新 huwen
static NSString *const VKFindPasswordURL = @"/plat2/app/sales/findPwd?";     //找回密码 刷新token，暂时未定

static NSString *const VKGetHouseFindStruURL = @"/plat2/app/house/getHouseFindStru?";     //获取房源查询条件数据集(销控和意向) v-2.0---
static NSString *const VKGetHouseListURL = @"/plat2/app/house/getHouseList?";       //获取房源销控查询结果列表(销控) v-2.0---
static NSString *const VKGetHouseWillListURL = @"/plat2/app/will/getHouseWillList?";     //获取意向落位查询结果列表 v-2.0---
static NSString *const VKGetHouseInfoURL = @"/plat2/app/house/getHouseInfo?";     //获取销控房源详情(销控) v-2.0---
static NSString *const VKGetHouseWillInfoURL = @"/plat2/app//will/getHouseWillInfo?";     //获取意向落位房源详情 v-2.0---

static NSString *const VKGetSalesYeJiURL = @"/plat2/app/sales/getSalesYeJi?";     //获取置业顾问业绩 v-2.0---
static NSString *const VKGetTransListWithProURL = @"/plat2/app/sales/getTransList?";     //获取成交数据列表 v-2.0---



/***********************************新销售家接口************************************************/


//业绩主页面
static NSString *const VKPerformanceMainURL = @"salesHomeSvc/reportConsultantPerMain";
//个人业绩签约认购详情
static NSString *const VKPerformanceDetailURL = @"salesHomeSvc/reportConsultantPerDetail";


//登录---
static NSString *const VKLoginRequestURLNew = @"userSvc/login";

//客户导出
//static NSString *const VKClientExportURL = @"customerSvc/list/user";
//static NSString *const VKClientListDetailURL = @"customerSvc/list/detail"; //客户列表详情

//客户列表详情
static NSString *const VKClientListDetailURL = @"relationLeadsCustomerSvc/search/view/CusDetailList";

//交易客户列表详情(认筹，认购，签约，回款)
static NSString *const VKTradeClientListDetailURL = @"relationCustomerTradeSvc/search/view/TradeView";

//查询客户--客户详情 /Query
static NSString *const VKQueryClientInfoURL = @"customerSvc/opportunityCustomerDetail";

//查询客户
static NSString *const VKCheckClientURL = @"leadsSvc/insertCheck";

//首页获取到访记录
static NSString *const VKGetVisitCountURL = @"customerFollowUpInfoSvc/StatisticsVisitCountByDay";

//客户新增
static NSString *const VKInsertClientInfoURL = @"customerSvc/save";

//客户信息修改
static NSString *const VKUpdateClientInfoURL = @"customerSvc/update";

//@"customerSvc/list/group"; //客户分组
static NSString *const VKClientGroupInfoURL = @"customerSvc/customerGroup";

//机会客户跟进记录新增
static NSString *const VKInsertClientVisitURL = @"customerFollowUpInfoSvc/insert";

//线索客户跟进记录新增
static NSString *const VKInsertLeadsVisitURL = @"leadsFollowUpInfoSvc/insert";

//客户跟进记录查询
static NSString *const VKClientVisitURL = @"cusBehaviorSvc/search/view/CusVisitView";

//客户历史记录查询
static NSString *const VKClientVisitHistoryURL = @"cusBehaviorSvc/search/view/CustomerHistoryView";

//抢客/转让
static NSString *const VKRobClientURL = @"customerSvc/dispatchCustomer";

//销售顾问列表(经理版)
static NSString *const VKConsultantListURL = @"customerSvc/Consultant/list";

//获取顾问当前项目所有客户
static NSString *const VKGetUserClienlistURL = @"relationLeadsCustomerSvc/search/view/CusSimpleListView";

//线索新增
static NSString *const VKLeadInsertURL = @"leadsSvc/insert";

//线索修改
static NSString *const VKLeadsUpdateURL = @"leadsSvc/update";

//线索详情
static NSString *const VKLeadsDetailURL = @"leadsSvc/leadsCustomerDetail";

//客户标签
static NSString *const VKCustomerLabelURL = @"labelCustomerSvc/customerLabelCount";

/********房源******/
//preselectionHouseSvc/salesExpert/batch/save
//批量设置客户意向落位
static NSString *const VKSaveDisposedHouseURL = @"preselectionHouseSvc/salesExpert/batchSave";

//批量删除客户意向落位
static NSString *const VKDeleteDisposedHouseURL = @"preselectionHouseSvc/batchTemp";

//获取楼栋下所有房源的意向落位列表
static NSString *const VKBuildingWillHouseListURL = @"preselectionHouseSvc/salesExpert/getDisposedHouseListByBuildingId";

//获取客户的意向落位列表
static NSString *const VKWillHouseListURL = @"preselectionHouseSvc/salesExpert/getDisposedHouseListByCustomerId";

//获取项目下分期与楼栋清单
static NSString *const VKStageBuildingListURL = @"houseTreeSvc/salesExpert/getStagesAndBuildingsByProjectIdAndSalesOrgId";

//获取意向落位房源的详情
static NSString *const VKWillHouseDetailURL = @"preselectionHouseSvc/salesExpert/getHouseDetailAndUserListByHouseId";

//获取楼栋下房源列表
static NSString *const VKBuildingResourceListURL = @"roomSvc/salesExpert/getHouseListByBuildingId";

//获取房源详情与记录
static NSString *const VKHouseDetailDealURL= @"roomSvc/getHouseD etailAndDealListByHouseIdAuth";//@"roomSvc/salesExpert/getHouseDetailAndDealListByHouseId";

//批量导入
static NSString *const VKBatchImportClientURL = @"leadsSvc/leadsBatchInsert";

//获取系统参数
static NSString *const VKSysListURL = @"dictSvc/list";

//根据顾问登录账号获取项目及分期清单
static NSString *const VKProjectInfoURL = @"saleTeamSvc/salesExpert/getProjectAndStageByAccountId";

//检查版本
static NSString *const VKCheckAppVersionURL = @"appVersionSvc/getAppVersion";
//意见反馈
static NSString *const VKAddSuggestionURL = @"appFeedbackSvc/addSuggestion";

//获取通知
static NSString *const VKGetNotificationURL = @"appNotifySvc/getAppNotify";

//获取新通知数量
static NSString *const VKGetNotificationCountURL = @"notificationCount";

//修改密码
static NSString *const VKModifyPasswordURL = @"userSvc/modifyPassword";

//修改性别
static NSString *const VKModifyUserInfoURL = @"userSvc/modifyUserInfo";

//根据顾问id获取销售组织和项目分期
static NSString *const VKGetViewByAccountURL = @"userSvc/search/list/ViewByAccount";

//阿里OSS访问权限STS验证接口
static NSString *const VKGetOssInfoURL = @"ossSvc/getOssInfo";

#endif /* VKRequestHeader_h */
