/*
 * Copyright 2014-2016 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ZYIOT_ZYIOTClientStateDelegate_h
#define ZYIOT_ZYIOTClientStateDelegate_h

#import <Foundation/Foundation.h>

/**
 * Notifies about ZYIOT client state changes and errors
 */
@protocol ZYIOTClientStateDelegate <NSObject>
@optional

/**
 * On successful start of ZYIOT client. ZYIOT client is successfully connected
 * to ZYIOT cluster and is ready for usage.
 */
- (void)onStarted;

/**
* On failure during ZYIOT client startup. Typically failure is related to
* network issues.
*/
- (void)onStartFailureWithException:(NSException *)exception;

/**
* On successful pause of ZYIOT client. ZYIOT client is successfully paused
* and does not consume any resources now.
*/
- (void)onPaused;

/**
* On failure during ZYIOT client pause. Typically related to
* failure to free some resources.
*/
- (void)onPauseFailureWithException:(NSException *)exception;

/**
* On successful resume of ZYIOT client. ZYIOT client is successfully connected
* to ZYIOT cluster and is ready for usage.
*/
- (void)onResume;

/**
* On failure during ZYIOT client resume. Typically failure is related to
* network issues.
*/
- (void)onResumeFailureWithException:(NSException *)exception;

/**
* On successful stop of ZYIOT client. ZYIOT client is successfully stopped
* and does not consume any resources now.
*/
- (void)onStopped;

/**
* On failure during ZYIOT client stop. Typically related to
* failure to free some resources.
*/
- (void)onStopFailureWithException:(NSException *)exception;

@end

#endif
