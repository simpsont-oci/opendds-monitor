#ifndef __DDS_TOPIC_MONITOR_H__
#define __DDS_TOPIC_MONITOR_H__

#include "first_define.h"

#include <dds/DCPS/TopicDescriptionImpl.h>
#include <dds/DCPS/OwnershipManager.h>
#include <dds/DCPS/EntityImpl.h>
#include <dds/DCPS/RecorderImpl.h>
#include <dds/DdsDcpsCoreC.h>
#include <dds/DCPS/Serializer.h>

#include <QString>

#include <memory>

/**
 * @brief Topic monitor for receiving raw DDS data samples.
 */
class TopicMonitor : public OpenDDS::DCPS::RecorderListener
{
public:

    /**
     * @brief Constructor for the DDS topic monitor.
     * @param[in] topicName The name of the topic to monitor.
     * @param[in] extensibility the topic extensibility.
     */
    TopicMonitor(const QString& topicName);

    /**
     * @brief Apply a filter to this topic.
     * @param[in] filter The SQL filter string for this topic.
     */
    void setFilter(const QString& filter);

    /**
    * @brief Get the current filter for this topic.
    * @return The current filter for this topic.
    */
    QString getFilter() const;

    /**
     * @brief Close the topic monitor for this topic.
     * @details This object doesn't delete properly from the
     *          OpenDDS::DCPS::Service_Participant::delete_recorder
     *          method, so we're forced to simply stop publishing
     *          updates and live with a memory leak.
     */
    void close();

    /**
     * @brief Read all the samples from the data reader.
     * @param[in] recorder The recorder object with the data.
     * @param[in] rawSample The new data sample for this topic.
     */
    virtual void on_sample_data_received(OpenDDS::DCPS::Recorder* recorder,
                                         const OpenDDS::DCPS::RawDataSample& rawSample);

    /**
     * @brief Callback for a newly discovered publisher for this topic.
     * @param[in] recorder The recorder object with the newly discovered match.
     * @param[in] status The status of the newly discovered match.
     */
    virtual void on_recorder_matched(OpenDDS::DCPS::Recorder* recorder,
                                     const DDS::SubscriptionMatchedStatus& status);

    /**
     * @brief Stop receiving samples.
     */
    void pause();

    /**
     * @brief Resume receiving samples.
     */
    void unpause();

    /**
     * @brief Destructor for the DDS topic monitor.
     */
    virtual ~TopicMonitor();

private:

    /// Stores the name of the topic.
    QString m_topicName;

    /// Stores the SQL filter if specified by the user.
    QString m_filter;

    /// Stores the typecode for this topic.
    const CORBA::TypeCode* m_typeCode;

    /// Stores the recorder object for this monitor.
    OpenDDS::DCPS::Recorder* m_recorder;

    /// Stores the topic object for this monitor.
    DDS::Topic* m_topic;

    /// The paused status of the data reader.
    bool m_paused;

    /// The topic extensibility
    OpenDDS::DCPS::Extensibility m_extensibility;

}; // End TopicMonitor

#endif

/**
 * @}
 */
