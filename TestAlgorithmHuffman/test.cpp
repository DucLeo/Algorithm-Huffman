#include "pch.h"
#include "gtest/gtest.h"
#include "..\HuffmanCoding\HuffmanTree.h"

TEST(Test_Encode) {
	HuffmanTree h;

	ASSERT_THROW(h.encode(""), logic_error);

	h.encodeString("it is test string");

	ASSERT_EQ(h.root->foo, 17);

	EoList<EoHuffmanTree*>* cur = h.listLeaf->head;

	ASSERT_EQ(cur->data->sym, 'i');
	ASSERT_EQ(cur->data->foo, 3);

	EoList<bool>* tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, 't');
	ASSERT_EQ(cur->data->foo, 4);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, ' ');
	ASSERT_EQ(cur->data->foo, 3);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, 's');
	ASSERT_EQ(cur->data->foo, 3);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, 'e');
	ASSERT_EQ(cur->data->foo, 1);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, 'r');
	ASSERT_EQ(cur->data->foo, 1);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, 'n');
	ASSERT_EQ(cur->data->foo, 1);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	cur = cur->next;
	ASSERT_EQ(cur->data->sym, 'g');
	ASSERT_EQ(cur->data->foo, 1);
	tmp = cur->data->codes->head;
	ASSERT_EQ(tmp->data, 1); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 0); tmp = tmp->next;
	ASSERT_EQ(tmp->data, 1);
	ASSERT_EQ(tmp, cur->data->codes->tail);

	ASSERT_EQ(cur, h.listLeaf->tail);

}

TEST(Test_EncodeString) {
	HuffmanTree h;

	ASSERT_THROW(h.encodeString(""), logic_error);

	ASSERT_EQ(h.encodeString("it is test string"), "11 01 000 11 001 000 01 1010 001 01 000 001 01 1011 11 1000 1001");
}

TEST(Test_SizeOriginal) {
	HuffmanTree h;

	ASSERT_THROW(h.sizeOriginal(), invalid_argument);

	h.encodeString("it is test string");

	ASSERT_EQ(h.sizeOriginal(), 17 * 8);
}

TEST(Test_SizeEncoded) {
	HuffmanTree h;

	ASSERT_THROW(h.sizeEncoded(), invalid_argument);

	h.encodeString("it is test string");

	ASSERT_EQ(h.sizeEncoded(), 48);
}

TEST(Test_DecodeString) {
	HuffmanTree h;

	ASSERT_THROW(h.decodeString(""), invalid_argument);

	ASSERT_EQ(h.decodeString(h.encodeString("it is test string")), "it is test string");

}

