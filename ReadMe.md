# Database Management Systems
## Chapter 1
### What is a DBMS?
* A very large, intergrated collection of data
* Models real-wrold enterprise.
	* Entities (e.g., students, courses)
	* Relationships (e.g., Madonna is taking CS564
* ***A Database Management System (DBMS)*** is a software package designed to store and manage databases. 

### Files vs. DBMS
If you use file systems for managing the data, you need to care about below things yourself.

* Application must stage large datasets between main memory and secondary storage (e.g., buffering, page-oriented access, 32-bit addressing, etc.)
* Special code for different queries
* Must protect data from inconsistency due to multiple concurrent users
* Crash recovery
* Security and access control

However, DBMS allows you to neglect these problems.  
Given all these advantages, is there ever a reason *not* to use a DBMS? Sometimes, yes. A DBMS is a complex piece of software, optimized for certain kinds of workloads (e.g., answering complex queries or handling many concurrent requests), and its performance may not be adequate for certain specialized applications. Examples include applications with tight real-time constraints or just a few well-defined critical operations for which efficient custom code must be written. Another reason for not using a DBMS is that an application may need to manipulate the data in ways not supported by the query language. In such a situdation, the abstract view of the data presented by the DBMS does not match the application's needs and actually gets in the way. As an example, relational databases do not support flexible analysis of text data.

### Why Use a DBMS?
DBMS provides several good featrues for managing collection of data. 

* Data independence and efficient access.
* Reduces application development time.
* Data integrity and security.
* Uniform data administration.
* Concurrent access, recovery from crashes.

### Why Study Database?
* Shift from ***computation*** to ***information***
	* at the "low end": scramble to webspace (a mess!)
	* at the "high end": scientific applications
* Datasets increasing in diversity and volume.
	* Digitla libraries, interactive video, Human Genome project, EOS project
	* ... need for DBMS exploding
* DBMS encompasses most of CS
	* OS, languages, theory, AI, multimedia, logic

### Data Models
* A ***data mdoel*** is a collection of concepts for describing data.
* A ***schema*** is a description of a particular collection of data, using the a given data model.
* The ***relational model of data*** is the most widely used model today.
	* Main concept: ***relation***, basically a table with rows and columns.
	* Every relation has a ***schema***, which describes the columns, or fields.

### Level of Abstraction
* Many ***views***, single ***conceptual (logial) schema*** and ***physical shcema.***
	* Views describe how users see the data.
	* Conceptual schema defines logical structures.
	* Physical schema describes the files and indexes used.
* Schemas are defined using DDL; data is modified/query using DML 

### Example: University Database
* Conceptual schema:
	* Students(sid: string, name: string, login: string, age: integer, gpa: real)
	* Courses(cid: string, cname: string, credits: integer)
	* Enrolled(sid: string, cid: string, grade: string)
* Physical schema:
	* Relations stored as unordered files.
	* Index on first columns of Students
* External schema (View):
	* Course_info(cid: string, enrollment: integer)

### Data Independence
* Applications insulated from how data is structured and stored.
* ***Logical data independence:*** Protection from changes in *logical* structure of data.
* ***Physical data independence:*** Protection from changes in *physical* structure of data.
* One of the most important benefits of using a DBMS!

### Concurrency Control
* Concurrent execution of user programs is essential for good DBMS performance.
	* Because disk access are frequent, and relatively slow, it is important to keep the cpu humming by working on several user programs concurrentrly.
* Interleaving actions of different user programs can lead to inconsistency: e.g., check is cleared while account balance is being computed.
* DBMS ensures such problems don't raise: users can pretend they are using a single-user system.

### Transaction: An Execution of a DB Program
* Key concept is ***transaction,*** which is an ***atomic*** sequence of database actions (reads/writes).
* Each transaction, exectued completely, must leave the DB in a ***consistent state*** if DB is consistent when the transaction begins.
	* Users can speicfy some simple ***integrity constraints*** on the data, and the DBMS will enforce these constraints.
	* Beyond this, the DBMS does not really understand the semantics of the data. (e.g., it does not understand how the interest on a bank account is computed).
	* Thus, ensuring that a transaction (run alone) preserves consistency is ultimately the **user's** responsibility!

### Scheduling Concurrent Transactions
* DBMS ensures that execution of` {T_1, ..., T_n}` is equivalent to some ***serial*** execution `T_1' ... T_n'`.
	* Before reading/writing an object, a transaction requests a lock on the object, and waits till the DBMS gives it the lock. All locks are released at the end of the transaction. **(Strict 2PL locking protocol.)**
	* **Idea:** If an action of `T_i` (say, writing X) affects `T_j` (which perhaps reads X), one of them, say `T_i`, will obtain the lock on X first and `T_j` is forced to wait until `T_i` completes; this effectively orders the transactions.
	* What if `T_j` already has a lock on Y and `T_i` later requests a lock on Y? **(Deadlock!)** `T_i` or `T_j` is **aborted** and restarted!

### Ensuring Atomicity 
* DBMS ensures ***atomicity*** (all-or-nothing property) even if system crashed in the middle of a Xact.
* **Idea:** Keep a ***log*** (history) of all actions carried out by the DBMS while executing a set of Xacts:
	* **Before** a change is made to the database, the corresponding log entry is forced to a safe location. (***WAL protocol***; OS support for this is often inadequate.)
	* After a crash, the effects of partially executed transactions are ***undone*** using the log. (Thanks to WAL, if log entry wasn't saved before the crash, corresponding change was not applied to database!) 

### The Log
* The following actions are recorded in the log:
	* ***T_i writes an object:*** the old value and the new value.
		* Log record must go to disk ***before** the changed page!
	* ***T_i commits/aborts:*** a log record indicating this actions.
* Log records chained together by Xact id, so it's easy to undo a specific Xact (e.g., to resolve a deadlock).
* Log is often *duplexed* and *archived* on "stable" storage.
* All log related activities (and in fact, all CC related activities such as lock/unlock, dealing with deadlocks etc.) are handled transparently by the DBMS.

### Structure of a DBMS
<img src=./Image/db1.png height = 300 />

* A typical DBMS has a layered architecture.
* The figure does not show the concurrency control and recovery components.
* This is one of several possible architectures; each system has its own variations.

### Summary 
* DBMS used to maintain, query large datasets.
* Benefits include recovery from system crashed, concurrent access, quick application development, data integrity and security.
* Levels of abstraction give data independence.
* A DBMS typically has a layered architecture.
