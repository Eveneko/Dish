#include "job.h"

Job::Job(ParsedJob& parsed_job, Environment& env, History* history) : env(env),h(history) {
    for (ParsedPipeline& parsed_pipeline : parsed_job.pipelines) {
        vector<Command> commands;

        for (ParsedCommand& parsed_command : parsed_pipeline.commands) {
            Command command(parsed_command, env,h);
            commands.push_back(command);
        }

        Pipeline pipeline(commands);
        pipelines.push_back(pipeline);
        parsed_pipelines.push_back(parsed_pipeline);
    }
}

void Job::RunAndWait(int job_source, int job_sink) {
    // ParsedPipeline pipeline = pipelines[0];
    // for (int i = 0; i < pipelines.size(); i++) {
    //     pipeline.RunAndWait(job_source, job_sink);
    //     Job updated_job = job_parser.Parse(pipeline.remaining_job_str, env);
    //     pipeline = updated_job[0]; //ugly hack to get it to use variable
    //     //assignment from the first command run.
    // }
    if (pipelines.size() == 0) return;
    pipelines[0].RunAndWait(job_source, job_sink);
    // assumes follow will work, because it already did the first time &
    // string is identical
    ParsedJob latter = job_parser.Parse(parsed_pipelines[0].remaining_job_str, env,h);
    Job updated_job(latter, env,h);
    updated_job.RunAndWait(job_source, job_sink);
    // even grosser recursive implementation!
}

string Job::ToString() {
    string result = "Job:";
    for (Pipeline& pipeline : pipelines) {
        result += "\n\t" + pipeline.ToString();
    }
    return result;
}
