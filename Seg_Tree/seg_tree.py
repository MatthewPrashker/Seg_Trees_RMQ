class segTreeNode:
    
    def __init__(self, left: int, right: int, val:int):
        self.left = left
        self.right = right
        self.val = val
        self.left_node = None
        self.right_node = None

class NumArray:

    def build_seg_tree(self, left: int, right: int, nums: List[int]):
        if(left > right):
            return None
        if(left == right):
            return segTreeNode(left, right, nums[left])
        else:
            mid = (left + right)//2
            left_node = self.build_seg_tree(left, mid, nums)
            right_node = self.build_seg_tree(mid + 1, right, nums)
            root = segTreeNode(left, right, left_node.val + right_node.val)
            root.left_node = left_node
            root.right_node = right_node
            return root
        
        
    def update_util(self, root: segTreeNode, index: int, diff: int):
        if(not root): 
            return
        if(index < root.left or index > root.right):
            return
        root.val += diff
        self.update_util(root.left_node, index, diff)
        self.update_util(root.right_node, index, diff)
    
    def sumRange_util(self, root: segTreeNode, left: int, right: int):
        if(root.left == left and root.right == right):
            return root.val
        
        mid = (root.left + root.right) // 2
        if(right <= mid):
            return self.sumRange_util(root.left_node, left, right)
        if(left >= mid + 1):
            return self.sumRange_util(root.right_node, left, right)
        return self.sumRange_util(root.left_node, left, mid) + self.sumRange_util(root.right_node, mid + 1, right)
    
    
    def __init__(self, nums: List[int]):
        self.nums = nums
        self.root = self.build_seg_tree(0, len(nums) - 1, nums)

    def update(self, index: int, val: int) -> None:
        diff = val - self.nums[index]
        self.nums[index] = val
        self.update_util(self.root, index, diff)

    def sumRange(self, left: int, right: int) -> int:
        return self.sumRange_util(self.root, left, right)