//
//  IOTOnlineDelegate.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/12/3.
//  Copyright © 2018年 ZYIT All rights reserved.
//

#ifndef IOTOnlineDelegate_h
#define IOTOnlineDelegate_h
@protocol IOTOnlineDelegate
/**IOT连接成功*/
- (void)onIOTConnect;
/**IOT异常断开*/
- (void)onIOTDisConnect;
@end


#endif /* IOTOnlineDelegate_h */
