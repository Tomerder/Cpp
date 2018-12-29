#include <memory>

// Represents a task that requires some resources for its execution.
class task;

// Represents an entity that maintains a collection of tasks and schedules them for execution.
class scheduler;

// Checks whether the two specified tasks conflict.
bool do_tasks_conflict(
	std::unique_ptr<task> task1,
	std::unique_ptr<task> task2);
// Makes no sense. Should be task const& for both parameters.

// Checks whether the specified task is complete.
bool is_task_complete(std::unique_ptr<task>& task);
// Makes no sense. Should be task const&.

// Assigns the specified task to the specified scheduler for later execution.
void assign_task_to_scheduler(
	std::shared_ptr<task> t,
	std::shared_ptr<scheduler> s);
// shared_ptr<task> probably makes sense, but 's' should be a scheduler&.

// Creates a new task that is already preassigned to the specified scheduler.
std::unique_ptr<task> create_task_assigned_to_scheduler(
	scheduler& s);
// Probably should return shared_ptr<task>.

// Creates a new scheduler.
scheduler* create_scheduler();
// Very bad to return a raw owning pointer. Should be unique_ptr<scheduler> (which is
// convertible to shared_ptr<scheduler>, so it doesn't limit the caller).

// Retrieves the last task that was scheduled for execution by the specified scheduler.
task& get_last_scheduled_task(scheduler& s);
// Probably better to return shared_ptr<task> unless we know the returned object's lifetime
// tends to be very long. Depends on context.

int main()
{
	return 0;
}