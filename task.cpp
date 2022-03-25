#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
using namespace std;

// Show useful information
void help()
{
    cout << "Usage :-" << endl;
    cout << "$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list" << endl;
    cout << "$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order" << endl;
    cout << "$ ./task del INDEX            # Delete the incomplete item with the given index" << endl;
    cout << "$ ./task done INDEX           # Mark the incomplete item with the given index as complete" << endl;
    cout << "$ ./task help                 # Show usage" << endl;
    cout << "$ ./task report               # Statistics" << endl;
}

// Add new item to the task file
void add_new_item(int p, string task)
{

    vector<pair<int, string>> v;
    ifstream fin;
    string line;
    fin.open("task.txt");

    while (fin)
    {
        getline(fin, line);
        int size = line.size();
        int pos = -1;
        for (int i = 0; i < size; i++)
        {
            if (line[i] == ' ')
            {
                pos = i;
                break;
            }
        }

        string p = line.substr(0, pos);
        string task = line.substr(pos + 1, size - pos - 1);
        if (p.size() > 0 && task.size() > 0)
        {
            int priority = stoi(p);
            v.push_back({priority, task});
        }
    }
    fin.close();
    cout << "Added task: \"" << task << "\" with priority " << p << endl;
    v.push_back({p, task});
    sort(v.begin(), v.end());
    ofstream fout;
    fout.open("task.txt");
    for (auto num : v)
    {
        line = to_string(num.first) + " " + num.second;
        fout << line << endl;
    }
    fout.close();
}

// List all the pending tasks that are available in the task file
void list_item()
{
    ifstream fin;
    string line;
    fin.open("task.txt");
    int line_number = 0;
    while (fin)
    {
        getline(fin, line);
        int size = line.size();
        int pos = -1;
        for (int i = 0; i < size; i++)
        {
            if (line[i] == ' ')
            {
                pos = i;
                break;
            }
        }

        string p = line.substr(0, pos);
        string task = line.substr(pos + 1, size - pos - 1);
        if (p.size() > 0 && task.size() > 0)
        {
            line_number++;
            cout << line_number << ". " << task << " [" << p << "]" << endl;
        }
    }
    if (line_number == 0)
    {
        cout << "There are no pending tasks!" << endl;
    }
    fin.close();
}

// Delete a item using index from the task file
void delete_item(int index)
{
    vector<pair<string, string>> v;
    ifstream fin;
    string line;
    fin.open("task.txt");

    while (fin)
    {
        getline(fin, line);
        int size = line.size();
        int pos = -1;
        for (int i = 0; i < size; i++)
        {
            if (line[i] == ' ')
            {
                pos = i;
                break;
            }
        }

        string p = line.substr(0, pos);
        string task = line.substr(pos + 1, size - pos - 1);
        if (p.size() > 0 && task.size() > 0)
        {
            v.push_back({p, task});
        }
    }
    fin.close();
    int size_of_list = v.size();
    if (index <= size_of_list && index > 0)
    {
        v.erase(v.begin() + index - 1);
        cout << "Deleted task #" << index << endl;
        ofstream fout;
        fout.open("task.txt");
        for (auto num : v)
        {
            line = num.first + " " + num.second;
            fout << line << endl;
        }
        fout.close();
    }
    else
    {
        cout << "Error: task with index #" << index << " does not exist. Nothing deleted." << endl;
    }
}

// Mark an item as completed and add that item to the completed file
void mark_complete(int index)
{
    vector<pair<string, string>> v;
    ifstream fin;
    string line;
    fin.open("task.txt");

    while (fin)
    {
        getline(fin, line);
        int size = line.size();
        int pos = -1;
        for (int i = 0; i < size; i++)
        {
            if (line[i] == ' ')
            {
                pos = i;
                break;
            }
        }

        string p = line.substr(0, pos);
        string task = line.substr(pos + 1, size - pos - 1);
        if (p.size() > 0 && task.size() > 0)
        {
            v.push_back({p, task});
        }
    }
    fin.close();
    int size_of_list = v.size();
    if (index <= size_of_list && index > 0)
    {

        string completed = v[index - 1].second;

        v.erase(v.begin() + index - 1);
        ofstream fout;
        fout.open("task.txt");
        for (auto num : v)
        {
            line = num.first + " " + num.second;
            fout << line << endl;
        }
        fout.close();
        cout << "Marked item as done." << endl;

        vector<string> completed_tasks;
        fin.open("completed.txt");
        while (fin)
        {
            getline(fin, line);
            if (line.size() > 0)
            {
                completed_tasks.push_back(line);
            }
        }
        fin.close();
        completed_tasks.push_back(completed);
        fout.open("completed.txt");
        for (auto task : completed_tasks)
        {
            fout << task << endl;
        }
        fout.close();
    }
    else
    {
        cout << "Error: no incomplete item with index #" << index << " exists." << endl;
    }
}

// Show all the pending tasks and the completed tasks
void generate_report()
{
    ifstream fin;
    string line;
    fin.open("task.txt");
    vector<string> pending_tasks;

    while (fin)
    {
        getline(fin, line);
        int size = line.size();
        int pos = -1;
        for (int i = 0; i < size; i++)
        {
            if (line[i] == ' ')
            {
                pos = i;
                break;
            }
        }

        string p = line.substr(0, pos);
        string task = line.substr(pos + 1, size - pos - 1);
        if (p.size() > 0 && task.size() > 0)
        {
            string text = task + " [" + p + "]";
            pending_tasks.push_back(text);
        }
    }
    fin.close();
    cout << "Pending : " << pending_tasks.size() << endl;
    int index = 1;
    for (auto task : pending_tasks)
    {
        cout << index << ". " << task << endl;
        index++;
    }
    cout << endl;

    fin.open("completed.txt");
    vector<string> completed_tasks;

    while (fin)
    {
        getline(fin, line);
        if (line.size() > 0)
        {
            completed_tasks.push_back(line);
        }
    }
    fin.close();
    cout << "Completed : " << completed_tasks.size() << endl;
    index = 1;
    for (auto task : completed_tasks)
    {
        cout << index << ". " << task << endl;
        index++;
    }
}

int main(int argc, char *argv[])
{

    string current_exec_name = argv[0]; // Name of the current exec program
    vector<string> all_args;
    all_args.assign(argv + 0, argv + argc);

    // Execute HElP
    if (argc == 1 || (argc == 2 && all_args[1] == "help"))
    {
        help();
    }

    // Add a new Item in File
    if (argc == 2 && all_args[1] == "add")
    {
        cout << "Error: Missing tasks string. Nothing added!" << endl;
    }
    if (argc == 4 && all_args[1] == "add")
    {
        int p = stoi(all_args[2]);
        string task = all_args[3];
        add_new_item(p, task);
    }

    // List Items
    if (argc == 2 && all_args[1] == "ls")
    {
        list_item();
    }

    // Delete Item By Index
    if (argc == 2 && all_args[1] == "del")
    {
        cout << "Error: Missing NUMBER for deleting tasks." << endl;
    }
    if (argc == 3 && all_args[1] == "del")
    {
        int index = stoi(all_args[2]);
        delete_item(index);
    }

    // Mark a task as completed
    if (argc == 2 && all_args[1] == "done")
    {
        cout << "Error: Missing NUMBER for marking tasks as done." << endl;
    }
    if (argc == 3 && all_args[1] == "done")
    {
        int index = stoi(all_args[2]);
        mark_complete(index);
    }

    // Generate a Report
    if (argc == 2 && all_args[1] == "report")
    {
        generate_report();
    }

    return 0;
}
