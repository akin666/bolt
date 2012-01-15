
#ifndef ATLASNODE_H_
#define ATLASNODE_H_

	class AtlasNode
	{
	public:
		AtlasNode();
		AtlasNode( const AtlasNode& other );
		AtlasNode( const int& ax , const int& ay , const int& width );

		~AtlasNode();

		int x,y;
		int width;
	};

#endif /* ATLASNODE_H_ */
