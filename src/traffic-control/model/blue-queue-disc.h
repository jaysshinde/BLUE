/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 NITK Surathkal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Vivek Jain <jain.vivek.anand@gmail.com>
 *          Sandeep Singh <hisandeepsingh@hotmail.com>
 *          Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 */

#ifndef BLUE_QUEUE_DISC_H
#define BLUE_QUEUE_DISC_H

#include <queue>
#include "ns3/packet.h"
#include "ns3/queue-disc.h"
#include "ns3/nstime.h"
#include "ns3/boolean.h"
#include "ns3/data-rate.h"
#include "ns3/timer.h"
#include "ns3/event-id.h"
#include "ns3/random-variable-stream.h"

namespace ns3 {

class UniformRandomVariable;

class BlueQueueDisc : public QueueDisc
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * \brief BlueQueueDisc Constructor
   */
  BlueQueueDisc ();

  /**
   * \brief BlueQueueDisc Destructor
   */
  virtual ~BlueQueueDisc ();



  /**
   * \brief Set the limit of the queue in bytes or packets.
   *
   * \param lim The limit in bytes or packets.
   */
     enum
  {
    DTYPE_NONE,        //!< Ok, no drop
    DTYPE_FORCED,      //!< A "forced" drop
    DTYPE_UNFORCED,    //!< An "unforced" (random) drop
  };
  static constexpr const char* UNFORCED_DROP = "Unforced drop";  //!< Early probability drops
  static constexpr const char* FORCED_DROP = "Forced drop";      //!< Forced drops, m_qAvg > m_maxTh
 
  /**
   * \brief Get queue delay
   */
  Time GetQueueDelay (void);
  
  /**
   * Assign a fixed random variable stream number to the random variables
   * used by this model.  Return the number of streams (possibly zero) that
   * have been assigned.
   *
   * \param stream first stream index to use
   * \return the number of stream indices assigned by this model
   */
  int64_t AssignStreams (int64_t stream);

protected:
  /**
   * \brief Dispose of the object
   */
  virtual void DoDispose (void);

  /**
   * \brief Initialize the queue parameters.
   */
  virtual void InitializeParams (void);

  virtual bool DoEnqueue (Ptr<QueueDiscItem> item);
  virtual Ptr<QueueDiscItem> DoDequeue (void);
  virtual Ptr<const QueueDiscItem> DoPeek (void) const;
  virtual bool CheckConfig (void);

  /**
   * \brief Increment the value of marking probability
   */
  virtual void IncrementPmark (void);

  /**
   * \brief Decrement the value of marking probability
   */
  virtual void DecrementPmark (void);

  /**
   * \brief Check if a packet needs to be dropped due to probability drop
   * \returns false for no drop, true for drop
   */
  virtual bool DropEarly (void);

private:
 
 Ptr<UniformRandomVariable> m_uv;              //!< Rng stream

  // ** Variables supplied by user
  double m_Pmark;                               //!< Marking Probability
  uint32_t m_meanPktSize;                       //!< Average Packet Size
  double m_increment;                           //!< increment value for marking probability
  double m_decrement;                           //!< decrement value for marking probability
  Time m_freezeTime;                            //!< Time interval during which Pmark cannot be updated

  // ** Variables maintained by BLUE
  Time m_lastUpdateTime;                        //!< last time at which Pmark was updated
  Time m_idleStartTime;                         //!< Time when BLUE Queue Disc entered the idle period
  bool m_isIdle;                                //!< True if queue is Idle
};

} // namespace ns3

#endif // BLUE_QUEUE_DISC_H
