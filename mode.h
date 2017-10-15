#ifndef MODE_H
#define MODE_H

void SKIP(){};

struct node
{
  byte node_name;
  void (*node_start)();
  void (*node_loop)();
  void (*node_stop)();
  node *next;
};

class mode
{
  public:
    node *tail = NULL;
    node *head = NULL;
    node *current = NULL;
    void reg(byte _name, void (*_start)(), void (*_loop)(), void (*_stop)())
    {
      node *temp = new node;
      temp->next = NULL;
      temp->node_name = _name;
      temp->node_start = _start;
      temp->node_loop = _loop;
      temp->node_stop = _stop;
      if (head != NULL)
      {
        tail->next = temp;
        tail = temp;
      }
      else tail = head = temp;
    }
    void loop()
    {
      current->node_loop();
    }
    void change(byte _name)
    {
      current->node_stop();
      set(_name);
    }
    void set(byte _name)
    {
      current = head;
      while (current->node_name != _name) current = current->next;
      current->node_start();
    }
    byte get()
    {
      return current->node_name;
    }
};

mode mode;

#endif
