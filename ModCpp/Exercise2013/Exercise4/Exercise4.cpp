#include <memory>

// Represents a task that requires some resources for its execution.
class task;

// Represents an entity that maintains a collection of tasks and schedules them for execution.
class scheduler;

// TODO 1
//	Abusing smart pointers is just as bad -- or worse -- than not using them at all.
//	In each of the following cases, determine whether the function's signature makes sense.
//	If it doesn't, suggest a possible change that keeps the function's original intent.

// Checks whether the two specified tasks conflict.
bool do_tasks_conflict(std::unique_ptr<task> task1, std::unique_ptr<task> task2);

// Checks whether the specified task is complete.
bool is_task_complete(std::unique_ptr<task>& task);

// Assigns the specified task to the specified scheduler for later execution.
void assign_task_to_scheduler(std::shared_ptr<task> t, std::shared_ptr<scheduler> s);

// Creates a new task that is already preassigned to the specified scheduler.
std::unique_ptr<task> create_task_assigned_to_scheduler(scheduler& s);

// Creates a new scheduler.
scheduler* create_scheduler();

// Retrieves the last task that was scheduled for execution by the specified scheduler.
task& get_last_scheduled_task(scheduler& s);

int main()
{
	return 0;
}