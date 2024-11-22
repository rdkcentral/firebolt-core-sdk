/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "${info.title.lowercase}_impl.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.providers}
/* ${PROVIDERS} */${end.if.providers}

    // Methods
    /* requestUserInterest - Provide information about the entity currently displayed or selected on the screen. */
    InterestResult ContentImpl::requestUserInterest( const Discovery::InterestType& type, const Discovery::InterestReason& reason, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        InterestResult interest;
        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {
        
            JsonObject jsonParameters;
            Firebolt::Discovery::JsonData_InterestType jsonType = type;
            WPEFramework::Core::JSON::Variant typeVariant(jsonType.Data());
            jsonParameters.Set(_T("type"), typeVariant);
            Firebolt::Discovery::JsonData_InterestReason jsonReason = reason;
            WPEFramework::Core::JSON::Variant reasonVariant(jsonReason.Data());
            jsonParameters.Set(_T("reason"), reasonVariant);
            JsonData_InterestResult jsonResult;
            status = transport->Invoke("content.requestUserInterest", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Content.requestUserInterest is successfully invoked");
                InterestResult interestResult;
                interestResult.appId = jsonResult.AppId.Value();
                {
                    string identifiersStr;
                    jsonResult.Entity.Identifiers.ToString(identifiersStr);
                    interestResult.entity.identifiers = identifiersStr;
                    if (jsonResult.Entity.Info.IsSet()) {
                        interestResult.entity.info = std::make_optional<Entity::Metadata>();
                        if (jsonResult.Entity.Info.Title.IsSet()) {
                            interestResult.entity.info.value().title = jsonResult.Entity.Info.Title;
                        }
                        if (jsonResult.Entity.Info.Synopsis.IsSet()) {
                            interestResult.entity.info.value().synopsis = jsonResult.Entity.Info.Synopsis;
                        }
                        if (jsonResult.Entity.Info.SeasonNumber.IsSet()) {
                            interestResult.entity.info.value().seasonNumber = jsonResult.Entity.Info.SeasonNumber;
                        }
                        if (jsonResult.Entity.Info.SeasonCount.IsSet()) {
                            interestResult.entity.info.value().seasonCount = jsonResult.Entity.Info.SeasonCount;
                        }
                        if (jsonResult.Entity.Info.EpisodeNumber.IsSet()) {
                            interestResult.entity.info.value().episodeNumber = jsonResult.Entity.Info.EpisodeNumber;
                        }
                        if (jsonResult.Entity.Info.EpisodeCount.IsSet()) {
                            interestResult.entity.info.value().episodeCount = jsonResult.Entity.Info.EpisodeCount;
                        }
                        if (jsonResult.Entity.Info.ReleaseDate.IsSet()) {
                            interestResult.entity.info.value().releaseDate = jsonResult.Entity.Info.ReleaseDate;
                        }
                        if (jsonResult.Entity.Info.ContentRatings.IsSet()) {
                            interestResult.entity.info.value().contentRatings = std::make_optional<std::vector<Entertainment::ContentRating>>();
                            auto index(jsonResult.Entity.Info.ContentRatings.Elements());
                            while (index.Next() == true) {
                                Entertainment::ContentRating contentRatingsResult1;
                                Firebolt::Entertainment::JsonData_ContentRating jsonResult = index.Current();
                                {
                                    contentRatingsResult1.scheme = jsonResult.Scheme;
                                    contentRatingsResult1.rating = jsonResult.Rating;
                                    if (jsonResult.Advisories.IsSet()) {
                                        contentRatingsResult1.advisories = std::make_optional<std::vector<std::string>>();
                                        auto index(jsonResult.Advisories.Elements());
                                        while (index.Next() == true) {
                                            contentRatingsResult1.advisories.value().push_back(index.Current().Value());
                                        }
                                    }
                                }
                                interestResult.entity.info.value().contentRatings->push_back(contentRatingsResult1);
                            }
                        }
                    }
                    if (jsonResult.Entity.WaysToWatch.IsSet()) {
                        interestResult.entity.waysToWatch = std::make_optional<std::vector<Entertainment::WayToWatch>>();
                        auto index(jsonResult.Entity.WaysToWatch.Elements());
                        while (index.Next() == true) {
                            Entertainment::WayToWatch waysToWatchResult1;
                            Firebolt::Entertainment::JsonData_WayToWatch jsonResult = index.Current();
                            {
                                {
                                    if (jsonResult.Identifiers.AssetId.IsSet()) {
                                        waysToWatchResult1.identifiers.assetId = jsonResult.Identifiers.AssetId;
                                    }
                                    if (jsonResult.Identifiers.EntityId.IsSet()) {
                                        waysToWatchResult1.identifiers.entityId = jsonResult.Identifiers.EntityId;
                                    }
                                    if (jsonResult.Identifiers.SeasonId.IsSet()) {
                                        waysToWatchResult1.identifiers.seasonId = jsonResult.Identifiers.SeasonId;
                                    }
                                    if (jsonResult.Identifiers.SeriesId.IsSet()) {
                                        waysToWatchResult1.identifiers.seriesId = jsonResult.Identifiers.SeriesId;
                                    }
                                    if (jsonResult.Identifiers.AppContentData.IsSet()) {
                                        waysToWatchResult1.identifiers.appContentData = jsonResult.Identifiers.AppContentData;
                                    }
                                }
                                if (jsonResult.Expires.IsSet()) {
                                    waysToWatchResult1.expires = jsonResult.Expires;
                                }
                                if (jsonResult.Entitled.IsSet()) {
                                    waysToWatchResult1.entitled = jsonResult.Entitled;
                                }
                                if (jsonResult.EntitledExpires.IsSet()) {
                                    waysToWatchResult1.entitledExpires = jsonResult.EntitledExpires;
                                }
                                if (jsonResult.OfferingType.IsSet()) {
                                    waysToWatchResult1.offeringType = jsonResult.OfferingType;
                                }
                                if (jsonResult.HasAds.IsSet()) {
                                    waysToWatchResult1.hasAds = jsonResult.HasAds;
                                }
                                if (jsonResult.Price.IsSet()) {
                                    waysToWatchResult1.price = jsonResult.Price;
                                }
                                if (jsonResult.VideoQuality.IsSet()) {
                                    waysToWatchResult1.videoQuality = std::make_optional<std::vector<Entertainment::WayToWatchVideoQuality>>();
                                    auto index(jsonResult.VideoQuality.Elements());
                                    while (index.Next() == true) {
                                        waysToWatchResult1.videoQuality.value().push_back(index.Current().Value());
                                    }
                                }
                                auto index(jsonResult.AudioProfile.Elements());
                                while (index.Next() == true) {
                                            waysToWatchResult1.audioProfile.push_back(index.Current().Value());
                               }
                                if (jsonResult.AudioLanguages.IsSet()) {
                                    waysToWatchResult1.audioLanguages = std::make_optional<std::vector<std::string>>();
                                    auto index(jsonResult.AudioLanguages.Elements());
                                    while (index.Next() == true) {
                                        waysToWatchResult1.audioLanguages.value().push_back(index.Current().Value());
                                    }
                                }
                                if (jsonResult.ClosedCaptions.IsSet()) {
                                    waysToWatchResult1.closedCaptions = std::make_optional<std::vector<std::string>>();
                                    auto index(jsonResult.ClosedCaptions.Elements());
                                    while (index.Next() == true) {
                                        waysToWatchResult1.closedCaptions.value().push_back(index.Current().Value());
                                    }
                                }
                                if (jsonResult.Subtitles.IsSet()) {
                                    waysToWatchResult1.subtitles = std::make_optional<std::vector<std::string>>();
                                    auto index(jsonResult.Subtitles.Elements());
                                    while (index.Next() == true) {
                                        waysToWatchResult1.subtitles.value().push_back(index.Current().Value());
                                    }
                                }
                                if (jsonResult.AudioDescriptions.IsSet()) {
                                    waysToWatchResult1.audioDescriptions = std::make_optional<std::vector<std::string>>();
                                    auto index(jsonResult.AudioDescriptions.Elements());
                                    while (index.Next() == true) {
                                        waysToWatchResult1.audioDescriptions.value().push_back(index.Current().Value());
                                    }
                                }
                            }
                            interestResult.entity.waysToWatch->push_back(waysToWatchResult1);
                        }
                    }
                }
                interest = interestResult;
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }
        if (err != nullptr) {
            *err = status;
        }

        return interest;
    }


    // Events
    /* onUserInterest - Provide information about the entity currently displayed or selected on the screen. */
    static void onUserInterestInnerCallback( void* notification, const void* userData, void* jsonResponse )
    {
        WPEFramework::Core::ProxyType<JsonData_InterestEvent>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_InterestEvent>*>(jsonResponse));

        ASSERT(proxyResponse.IsValid() == true);

        if (proxyResponse.IsValid() == true) {
            InterestEvent interest;

            interest.appId = proxyResponse->AppId;
            interest.type = proxyResponse->Type;
            interest.reason = proxyResponse->Reason;
            {
                string identifiersStr;
                (*proxyResponse).Entity.Identifiers.ToString(identifiersStr);
                interest.entity.identifiers = identifiersStr;
                if ((*proxyResponse).Entity.Info.IsSet()) {
                    interest.entity.info = std::make_optional<Entity::Metadata>();
                    if ((*proxyResponse).Entity.Info.Title.IsSet()) {
                        interest.entity.info.value().title = (*proxyResponse).Entity.Info.Title;
                    }
                    if ((*proxyResponse).Entity.Info.Synopsis.IsSet()) {
                        interest.entity.info.value().synopsis = (*proxyResponse).Entity.Info.Synopsis;
                    }
                    if ((*proxyResponse).Entity.Info.SeasonNumber.IsSet()) {
                        interest.entity.info.value().seasonNumber = (*proxyResponse).Entity.Info.SeasonNumber;
                    }
                    if ((*proxyResponse).Entity.Info.SeasonCount.IsSet()) {
                        interest.entity.info.value().seasonCount = (*proxyResponse).Entity.Info.SeasonCount;
                    }
                    if ((*proxyResponse).Entity.Info.EpisodeNumber.IsSet()) {
                        interest.entity.info.value().episodeNumber = (*proxyResponse).Entity.Info.EpisodeNumber;
                    }
                    if ((*proxyResponse).Entity.Info.EpisodeCount.IsSet()) {
                        interest.entity.info.value().episodeCount = (*proxyResponse).Entity.Info.EpisodeCount;
                    }
                    if ((*proxyResponse).Entity.Info.ReleaseDate.IsSet()) {
                        interest.entity.info.value().releaseDate = (*proxyResponse).Entity.Info.ReleaseDate;
                    }
                    if ((*proxyResponse).Entity.Info.ContentRatings.IsSet()) {
                        interest.entity.info.value().contentRatings = std::make_optional<std::vector<Entertainment::ContentRating>>();
                        auto index((*proxyResponse).Entity.Info.ContentRatings.Elements());
                        while (index.Next() == true) {
                            Entertainment::ContentRating contentRatingsResult1;
                            Firebolt::Entertainment::JsonData_ContentRating jsonResult = index.Current();
                                contentRatingsResult1.scheme = jsonResult.Scheme;
                                contentRatingsResult1.rating = jsonResult.Rating;
                                if (jsonResult.Advisories.IsSet()) {
                                    contentRatingsResult1.advisories = std::make_optional<std::vector<std::string>>();
                                    auto index(jsonResult.Advisories.Elements());
                                    while (index.Next() == true) {
                                        contentRatingsResult1.advisories.value().push_back(index.Current().Value());
                                    }
                                }
                            interest.entity.info.value().contentRatings.value().push_back(contentRatingsResult1);
                        }
                    }
                }
                if ((*proxyResponse).Entity.WaysToWatch.IsSet()) {
                    interest.entity.waysToWatch = std::make_optional<std::vector<Entertainment::WayToWatch>>();
                    auto index((*proxyResponse).Entity.WaysToWatch.Elements());
                    while (index.Next() == true) {
                        Entertainment::WayToWatch waysToWatchResult1;
                        Firebolt::Entertainment::JsonData_WayToWatch jsonResult = index.Current();
                            {
                                if (jsonResult.Identifiers.AssetId.IsSet()) {
                                    waysToWatchResult1.identifiers.assetId = jsonResult.Identifiers.AssetId;
                                }
                                if (jsonResult.Identifiers.EntityId.IsSet()) {
                                    waysToWatchResult1.identifiers.entityId = jsonResult.Identifiers.EntityId;
                                }
                                if (jsonResult.Identifiers.SeasonId.IsSet()) {
                                    waysToWatchResult1.identifiers.seasonId = jsonResult.Identifiers.SeasonId;
                                }
                                if (jsonResult.Identifiers.SeriesId.IsSet()) {
                                    waysToWatchResult1.identifiers.seriesId = jsonResult.Identifiers.SeriesId;
                                }
                                if (jsonResult.Identifiers.AppContentData.IsSet()) {
                                    waysToWatchResult1.identifiers.appContentData = jsonResult.Identifiers.AppContentData;
                                }
                            }
                            if (jsonResult.Expires.IsSet()) {
                                waysToWatchResult1.expires = jsonResult.Expires;
                            }
                            if (jsonResult.Entitled.IsSet()) {
                                waysToWatchResult1.entitled = jsonResult.Entitled;
                            }
                            if (jsonResult.EntitledExpires.IsSet()) {
                                waysToWatchResult1.entitledExpires = jsonResult.EntitledExpires;
                            }
                            if (jsonResult.OfferingType.IsSet()) {
                                waysToWatchResult1.offeringType = jsonResult.OfferingType;
                            }
                            if (jsonResult.HasAds.IsSet()) {
                                waysToWatchResult1.hasAds = jsonResult.HasAds;
                            }
                            if (jsonResult.Price.IsSet()) {
                                waysToWatchResult1.price = jsonResult.Price;
                            }
                            if (jsonResult.VideoQuality.IsSet()) {
                                waysToWatchResult1.videoQuality = std::make_optional<std::vector<Entertainment::WayToWatchVideoQuality>>();
                                auto index(jsonResult.VideoQuality.Elements());
                                while (index.Next() == true) {
                                    waysToWatchResult1.videoQuality.value().push_back(index.Current().Value());
                                }
                            }
                            auto index(jsonResult.AudioProfile.Elements());
                            while (index.Next() == true) {
                                waysToWatchResult1.audioProfile.push_back(index.Current().Value());            
                            }
                            if (jsonResult.AudioLanguages.IsSet()) {
                                waysToWatchResult1.audioLanguages = std::make_optional<std::vector<std::string>>();
                                auto index(jsonResult.AudioLanguages.Elements());
                                while (index.Next() == true) {
                                    waysToWatchResult1.audioLanguages.value().push_back(index.Current().Value());
                                }
                            }
                            if (jsonResult.ClosedCaptions.IsSet()) {
                                waysToWatchResult1.closedCaptions = std::make_optional<std::vector<std::string>>();
                                auto index(jsonResult.ClosedCaptions.Elements());
                                while (index.Next() == true) {
                                    waysToWatchResult1.closedCaptions.value().push_back(index.Current().Value());
                                }
                            }
                            if (jsonResult.Subtitles.IsSet()) {
                                waysToWatchResult1.subtitles = std::make_optional<std::vector<std::string>>();
                                auto index(jsonResult.Subtitles.Elements());
                                while (index.Next() == true) {
                                    waysToWatchResult1.subtitles.value().push_back(index.Current().Value());
                                }
                            }
                            if (jsonResult.AudioDescriptions.IsSet()) {
                                waysToWatchResult1.audioDescriptions = std::make_optional<std::vector<std::string>>();
                                auto index(jsonResult.AudioDescriptions.Elements());
                                while (index.Next() == true) {
                                    waysToWatchResult1.audioDescriptions.value().push_back(index.Current().Value());
                                }
                            }
                        interest.entity.waysToWatch.value().push_back(waysToWatchResult1);
                    }
                }
            }

            proxyResponse.Release();

            IContent::IOnUserInterestNotification& notifier = *(reinterpret_cast<IContent::IOnUserInterestNotification*>(notification));
            notifier.onUserInterest(interest);
        }
    }
    void ContentImpl::subscribe( IContent::IOnUserInterestNotification& notification, Firebolt::Error *err )
    {
        const string eventName = _T("content.onUserInterest");
        Firebolt::Error status = Firebolt::Error::None;

        JsonObject jsonParameters;

        status = FireboltSDK::Event::Instance().Subscribe<JsonData_InterestEvent>(eventName, jsonParameters, onUserInterestInnerCallback, reinterpret_cast<void*>(&notification), nullptr);

        if (err != nullptr) {
            *err = status;
        }
    }
    void ContentImpl::unsubscribe( IContent::IOnUserInterestNotification& notification, Firebolt::Error *err )
    {
        Firebolt::Error status = FireboltSDK::Event::Instance().Unsubscribe(_T("content.onUserInterest"), reinterpret_cast<void*>(&notification));

        if (err != nullptr) {
            *err = status;
        }
    }


}//namespace ${info.Title}
}${end.if.implementations}

${if.enums}

namespace WPEFramework {

/* ${ENUMS} */
}${end.if.enums}

