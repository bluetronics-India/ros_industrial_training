#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
//#include <lesson_actions/FibonacciAction.h>

class FibonacciAction
{
protected:

  ros::NodeHandle nh_;
  
//  actionlib::SimpleActionServer<lesson_actions::FibonacciAction> as_; 
  std::string action_name_;
  
//  lesson_actions::FibonacciFeedback feedback_;
//  lesson_actions::FibonacciResult result_;

public:

  FibonacciAction(std::string name) :
    as_(nh_, name, boost::bind(&FibonacciAction::executeCB, this, _1), false),
    action_name_(name)
  {
//    as_.start();
  }

  ~FibonacciAction(void) {}

  void executeCB(const lesson_actions::FibonacciGoalConstPtr &goal)
  {
    ros::Rate r(1);
    bool success = true;

    // seed fibonacci sequence
    feedback_.sequence.clear();
    feedback_.sequence.push_back(0);
    feedback_.sequence.push_back(1);

    ROS_INFO("%s: Executing, creating fibonacci sequence of order %i with seeds %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);

    // start executing the action
    for(int i=1; i<=goal->order; i++)
    {
      // check that preempt has not been requested by the client
//      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
//        as_.setPreempted(); // set the action state to preempted
        success = false;
        break;
      }
//      feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
//      as_.publishFeedback(feedback_); // publish the feedback
      
      r.sleep(); // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
    }

    if(success)
    {
      result_.sequence = feedback_.sequence;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
//      as_.setSucceeded(result_);
    }
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fibonacci");

  FibonacciAction fibonacci(ros::this_node::getName());
  ros::spin();

  return 0;
}
