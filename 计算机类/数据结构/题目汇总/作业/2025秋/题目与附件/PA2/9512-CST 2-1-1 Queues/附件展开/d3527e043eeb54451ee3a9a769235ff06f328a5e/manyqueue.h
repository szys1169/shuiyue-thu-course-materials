class QueueManager{
public:
    QueueManager(unsigned int m);
    void push(unsigned int k, unsigned int x);
    void pop(unsigned int k);
    unsigned int query(unsigned int k, unsigned int i);
    ~QueueManager();
private:
    //TODO
};