#include <QCoreApplication>
#include <QAtomicPointer>
#include <QElapsedTimer>
#include <QThread>
#include <QDebug>

enum
{
	NumNode = 2000000,
	NumThread = 4
};


struct Node final
{
	Node *next = nullptr;
};

#if 0
class Stack
{
	Node *head = nullptr;
	QMutex mutex;
public:
	void push(Node *n)
	{
		QMutexLocker locker(&mutex);
		n->next = head;
		head = n;
	}
	Node *pop()
	{
		QMutexLocker locker(&mutex);
		Node *n = head;
		if (n)
			head = n->next;
		return n;
	}
};
#else
class Stack final
{
	QAtomicPointer<Node> m_head = nullptr;
public:
	void push(Node *n)
	{
		do
		{
			n->next = m_head;
		} while (!m_head.testAndSetOrdered(n->next, n));
	}
	Node *pop()
	{
		Node *n;
		do
		{
			n = m_head;
			if (!n)
				return nullptr;
		} while (!m_head.testAndSetOrdered(n, n->next));
		return n;
	}
};
#endif

struct Pusher final : QThread
{
	Stack *stack{};
	void run() override
	{
		for (auto f = 0; f < NumNode / NumThread; f++)
		{
			stack->push(new Node);
		}
	}
};

struct Popper final : QThread
{
	Stack *stack{};
	int count{};
	void run() override
	{
		count = 0;
		auto n = stack->pop();
		while (n)
		{
			delete n;
			++count;
			n = stack->pop();
		}
	}
};

int main()
{
	Stack stack;

	{
		QElapsedTimer timer;
		Pusher pushers[NumThread];
		timer.start();
		for (auto& pusher : pushers)
		{
			pusher.stack = &stack;
			pusher.start();
		}
		for (auto& pusher : pushers)
		{
			pusher.wait();
		}
		qDebug() << "Pushed done in" << timer.elapsed() << "ms.";
	}

	{
		QElapsedTimer timer;
		Popper poppers[NumThread];
		timer.start();
		for (auto& popper : poppers)
		{
			popper.stack = &stack;
			popper.start();
		}
		auto total = 0;
		auto diff = 0;
		for (auto& popper : poppers)
		{
			popper.wait();
			total += popper.count;
			diff += qAbs((NumNode / NumThread) - popper.count);
		}
		qDebug() << "Destroyed" << total << "node in" << timer.elapsed() << "ms.";
		qDebug() << "Difference:" << diff / NumThread;
	}
	return 0;
}
