class listNode {
    constructor(value, prev = null, next = null) {
        this.value = value
        this.prev = prev
        this.next = next
    }
}

class linkedList {
    constructor() {
            this.head = this.tail = null
        }
        // add to the end of the list
    append(value) {
        if (!this.tail) {
            this.tail = this.head = new listNode(value);
        } else {
            let oldTail = this.tail;
            this.tail = new listNode(value);
            this.tail.prev = oldTail
            oldTail.next = this.tail
        }
    }

    // add to the start of the list
    prepend(value) {
        if (!this.head) {
            this.head = this.tail = new listNode(value);
        } else {
            let oldHead = this.head
            this.head = new listNode(value);
            this.head.next = oldHead
            oldHead.prev = this.head
        }
    }

    deleteHead() {
        if (!this.head) {
            return null
        } else {
            let removedHead = this.head
            if (this.head === this.tail) {
                this.head = this.tail = null
            } else {
                this.head = this.head.next
                this.head.prev = null
            }
            return removedHead.value;
        }
    }

    deleteTail() {
        if (!this.tail) {
            return null
        } else {
            let removedTail = this.tail
            if (this.tail === this.head) {
                this.tail = this.head = null
            } else {
                this.tail = this.tail.prev
                this.tail.next = null
            }
            return removedTail
        }
    }

    search(value) {
        let node = this.head
        while (node) {
            if (node.value === value) {
                return node
            }
            node = node.next
        }
        return null
    }
}

let list = new linkedList();
list.append(1);
list.append(2);
list.append(3);

list.prepend(0);
list.prepend(-1);

console.log(list)
