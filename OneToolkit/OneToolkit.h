// (c) 2021 JUV Studios. All rights reserved. Included as part of OneToolkit for use in C++ projects targeting the Windows platform.

#pragma once
#include <juv.h>
#include <concepts>
#include <unknwn.h>
#include <Windows.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/OneToolkit.System.h>
#include <winrt/OneToolkit.Storage.h>
#include <winrt/OneToolkit.Runtime.h>
#include <winrt/OneToolkit.Lifecycle.h>
#include <winrt/OneToolkit.UI.Input.h>
#include <winrt/OneToolkit.Media.Imaging.h>

namespace winrt::OneToolkit
{
	/// <summary>
	/// Represents a type which can be passed through the Windows Runtime ABI.
	/// </summary>
	template <typename T>
	concept WindowsRuntimeType = winrt::impl::has_category_v<T>;

	namespace Runtime
	{
		/// <summary>
		/// Represents a dynamic link library and enables the ability to use exported functions or variables.
		/// </summary>
		struct DynamicLibrary
		{
		public:
			/// <summary>
			/// Creates a new instance of DynamicLibrary from a DLL file name.
			/// </summary>
			/// <param name="fileName">The file name of the DLL that you want to load into the process.</param>
			/// <param name="isPackagedLibrary">Indicates whether the DLL is inside the app package or not.</param>
			DynamicLibrary(hstring const& fileName, bool isPackagedLibrary = false) : m_FileName(fileName), m_IsPackagedLibrary(isPackagedLibrary)
			{
				Handle(isPackagedLibrary ? LoadPackagedLibrary(fileName.data(), 0) : WINRT_IMPL_LoadLibraryW(fileName.data()));
			}

			/// <summary>
			/// Creates a new instance of DynamicLibrary that's a copy of an existing instance.
			/// </summary>
			/// <param name="another">The existing instance to copy from.</param>
			DynamicLibrary(DynamicLibrary const& another)
			{
				Copy(another);
			}

			/// <summary>
			/// Creates a new instance instance of DynamicLibrary by moving an existing instance.
			/// </summary>
			/// <param name="another">The existing instance to move from.</param>
			DynamicLibrary(DynamicLibrary&& another) noexcept
			{
				Move(std::move(another));
			}

			/// <summary>
			/// Gets the handle to the loaded DLL.
			/// </summary>
			auto Handle() const noexcept
			{
				return m_Handle;
			}

			/// <summary>
			/// Gets the file name of the DLL.
			/// </summary>
			const auto FileName() const noexcept
			{
				return m_FileName;
			}

			DynamicLibrary& operator=(const DynamicLibrary& another)
			{
				Copy(another);
				return *this;
			}

			DynamicLibrary& operator=(DynamicLibrary&& another) noexcept
			{
				Move(std::move(another));
				return *this;
			}

			bool operator==(DynamicLibrary const& another) const noexcept
			{
				return m_IsPackagedLibrary == another.m_IsPackagedLibrary && m_Handle == another.m_Handle;
			}

			bool operator!=(DynamicLibrary const& another) const noexcept
			{
				return !operator==(another);
			}

			/// <summary>
			/// Retrieves the address of an exported function or variable.
			/// </summary>
			template <typename Pointer>
			auto GetProcAddress(std::string_view procName) const requires std::is_pointer_v<Pointer>
			{
				auto result = WINRT_IMPL_GetProcAddress(m_Handle, procName.data());
				if (!result) throw_last_error();
				return reinterpret_cast<Pointer>(result);
			}

			~DynamicLibrary()
			{
				if (m_Handle) WINRT_IMPL_FreeLibrary(m_Handle);
			}
		private:
			HMODULE m_Handle;

			hstring m_FileName;

			bool m_IsPackagedLibrary;

			void Handle(void* newHandle)
			{
				if (!newHandle) throw_last_error();
				m_Handle = static_cast<HMODULE>(newHandle);
			}

			void Copy(DynamicLibrary const& another)
			{
				if (another == *this) return;
				Handle(another.m_IsPackagedLibrary ? LoadPackagedLibrary(another.m_FileName.data(), 0) : WINRT_IMPL_LoadLibraryW(another.m_FileName.data()));
				m_FileName = another.m_FileName;
				m_IsPackagedLibrary = another.m_IsPackagedLibrary;
			}

			void Move(DynamicLibrary&& another) noexcept
			{
				if (another == *this� � � � t ^ ^ � � \ � � � � � � � � \ � � \ � � � � � � � � � \ � � � ^ � � � � � � � � � � � � � � � � � � � � ^ � � � � � ^ � � b n � l � p Z � � � � Z h r � � Z r � r r Z r f � r r � ` � n f p � ^ � � � � � � � � � � D X D � � � � � � � � � � � � � � � � � � � � D t D ` � j d � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � z D X D � � � � � � � � � � � � � � � � � � � � � � � � � � � � � D t D � � � d j l D �   �   nk  27j����   �          ��������   2 ��������        "   N       $   e76697ef-e6bc-4f4e-9667-f898ba28062c��    m
�@��(O�K��V�`9    hbin �                        ����nk  o���   �`         �� ����    �����   ����                      DownloadStatsk ����lf �� RawB8� ValiH   S - 1 - 5 - 1 8    0   vk   �         ExtendedErrorCodetState ����nk  ��_F���    �         ��������   @!  �   ����                     RawBytes����nk  ��_F���    �         ��������   X"  �   ����                  
   ValidByteswBytes����nk  o���   �`          ��������    �����   ����                       UploadStats   0 ����vk    �F        Ranku y �   �l  �   vk   �         DownloadModea d �   nk  ��`����   �          ��������   ؄ ��������        "   N       $   6b01b525-bab3-45de-9bb4-327aac355c4f`� P   ����        4   �      (   a8c1f8621c471206fa6a6b38ef173b068dcd7a90   P ����nk  h<D���   @`          ��������
   �7  �   ����        .   �         Files_0t����c 5 a 2 6 8 f 5 3 8 a 5 e 1 e 9 b 1 b 8 3 7 0 0 1 5 b 4 a 4 3 1 8 d 0 e c b 8 2     ����{ 6 D 9 D 1 8 F D - 3 3 1 9 - 4 C 9 7 - B 3 A F - A F E 5 8 1 1 3 3 E 9 F }   0 e 3 ����vk
   ����       ExpiredMapnd(  ����vk    h       peerHttp�    0 P 8&  p `&  �&  � � �&  �&  �'   '  8'  �)  h*  �1  �  �R  H� @� `�  � (� �� �� �� � � H� x� У ��    p ����u 6 Z 0 + Z E o 3 U a x u y y n . 4 1 . 1 . 7 . 1 . 0 . 0 . 2 2 . 3 5   F } p   nk  be����   ��         ��������	   �g  ��������        $   4         Files_0    �\   ]  (]  �]  �]  ����vk   �        ExpiredMapSize ����vk �  �      CdnURL  �   �D  (E  HE  X� hE  �   `  �E  �E  �b  �a  �b   c   c  �c  �c  �c  x� �� @  �   �   � H� HS  �� P� �  @ p    �g  (���h t t p : / / t l u . d l . d e l i v e r y . m p . m i c r o s o f t . c o m / f i l e s t r e a m i n g s e r v i c e / f i l e s / 6 7 4 d 6 2 5 3 - 0 c b e - 4 c 2 9 - 8 f 8 9 - 9 a 4 a b d f 0 9 1 3 f ? P 1 = 1 6 3 4 6 1 3 7 6 3 & P 2 = 4 0 4 & P 3 = 2 & P 4 = P X e E B I % 2 f c 7 n L m l Q z M L p c % 2 f f y R G C % 2 b 3 F 4 l u j H T 6 w H 2 M A H U 9 O s i I X u % 2 f K A 9 w X J X B k P k 2 g T D b b c y i r R H r 7 b 8 p m h J t C i 8 w % 3 d % 3 d      �t�L�G�����Vali����C : \ W i n d o w s \ S e r v i c e P r o f i l e s \ N e t w o r k S e r v i c e \ A p p D a t a \ L o c a l \ M i c r o s o f t \ W i n d o w s \ D e l i v e r y O p t i m i z a t i o n \ C a c h e \ 2 5 b 2 0 6 9 c a d 8 4 9 5 d a b 6 f f 3 d a 6 d d 5 4 5 7 4 8 4 c e c 4 0 0 4   �   nk  j{θ���   �          ��������    �v  ��������        4   2      (   10fc77f0c53b789e2f80e844b85a3492d604e4f5   �_  ����vk	   �        caPeerCountonCount�   �D  (E  HE  X� hE  �   `  �E  �E  �b  �a  �b   c   c  �c  �c  �c  x� �� @  �   �   � H� HS  �� P� �  @ p p� P
 P      peerHttp@   �j  @� h� �� 0+ (   vk    �        OwnerIdentityd  (���h t t p : / / t l u . d l . d e l i v e r y . m p . m i c r o s o f t . c o m / f i l e s t r e a m i n g s e r v i c e / f i l e s / 6 7 4 d 6 2 5 3 - 0 c b e - 4 c 2 9 - 8 f 8 9 - 9 a 4 a b d f 0 9 1 3 f ? P 1 = 1 6 3 4 6 1 3 7 6 3 & P 2 = 4 0 4 & P 3 = 2 & P 4 = P X e E B I % 2 f c 7 n L m l Q z M L p c % 2 f f y R G C % 2 b 3 F 4 l u j H T 6 w H 2 M A H U 9 O s i I X u % 2 f K A 9 w X J X B k P k 2 g T D b b c y i r R H r 7 b 8 p m h J t C i 8 w % 3 d % 3 d     T��     T��                                     T��                                             �                                           �������       0 4 p  2 5 3 2 c 2 c c e 0 2 b f 1 5 2 b 2 d 4 0 f a 8 8 c 4 a c c   cheHos(  vk	   �          CacheHost� �  @   ��     �� 0   vk    ��      DownloadDurationMsecslath   vk H   ��       CorrelationVector� 0� 8   �� � �� (   vk    @�       CachedBytesnloadX  W U   C l i e n t   D o w n l o a d    H� (  �� � �    Http  s y T O p s z T m 0 e v O k G a . 0 . 4 . 1 . 0 . 0 . 2 5 . 1 . 1 . 6       �   nk  '����   �          ��������    ������������                       DownloadStats   `   nk  Sg��   @�         ��������   �� ��������                     RawBytes   ype3hbin    @                          � ����S - 1 - 5 - 1 8         vk   �        DoStatee����vk N           U CorrelationVector . 1 . 8  3 d Q j z q N P T U 2 h F M d S . 6 2 . 1 . 7 . 1 . 0 . 0 . 9 . 1 . 1 . 2 2     `  �   vk N   H8      6aUpdateId    vk   �         Flags   @   vk   �        NumProps    vk     ��      DoTimes     vk R   �       FileId6 0   vk �   �=       HashID    �	      �P$   �i         ����vk   �         PropValPropType6h  2 e 1 a 0 c 3 8 b b f c 6 4 3 4 8 e 3 9 6 a b 1 2 f f d b e 7 6 8 2 9 d b b 0 6    X   nk  �\����   �1          ��������   !  ��������                     RawBytes�   nk  ��2���   h^          ��������    ������������                       DownloadStatsf  X   nk  `f^����   H�         ��������	    � ��������        $   2         Files_0 ����nk  h<D���   �         � ����   pM  �   ����       "   N       $   a99c641f-9110-44e3-8f7a-0772a474023e � ����vk   �        Upload ����vk
   p�       WorkingDirtegrit����z,g�F28K�!�߮-�C        vk �   �q       HashIDwBx���0 7 f c b b b 5 e d 5 5 d 7 6 f 6 d 1 0 c 4 5 b 8 3 d 2 a 5 d 9 4 6 d e 6 5 5 3 7 2 a 4 a d e 8 5 0 8 8 b 7 0 4 6 2 5 9 e 1 c 8   . ����vk    �     1 peerHttp����vk   �        7 Have8 f ����vk   �       b HaveSize8   8 L k R 7 j t S 0 0 W m R l z a . 1 . 1 . 3 . 1     ����vk    �        peerHttp����vk
 &   ��       CallerName  Http����nk  �)N���   �         �  ����    X' �   ����       4   �      (   25b2069cad8495dab6ff3da6dd5457484cec4004����vk   �        Status  ����5     ` ����vk           PeerId�����vk	   �         CacheHost �� ����        0 ����vk    P       DownloadDurationMsecs   ����vk L   '      CorrelationVector `    �37     File����vk    �     liCachedBytes���  �K�     �K�                                     �K�                                             ��                                            �������           h                  h                                             ��                                            �������        a 0 �  vk   �        1 IsPinned�  C : \ W i n d o w s \ S e r v i c e P r o f i l e s \ N e t w o r k S e r v i c e \ A p p D a t a \ L o c a l \ M i c r o s o f t \ W i n d o w s \ D e l i v e r y O p t i m i z a t i o n \ C a c h e \ 9 c e d d f 6 5 6 3 e 5 d c a e d 8 9 4 0 0 f 6 d 1 9 0 d a c 3 9 a 5 2 6 d d 2   X   vk
 &   �	       CallerName E  0   W U   C l i e n t   D o w n l o a d     `� 8   vk   �         CacheServerConnectionCount   3    �$*     Httpx���8             �      L<      =>      x<      {      �<      e�      :=      ��      �@      �6     �      �8     �      �:     �      �<     /      J?     �      �C     �       �D     �      �J     "      ]L     �      VN      3      ��     o?      {�     �L      f     e      �s     ��      �e           -y     �      Z�     �      ��     �$      ��     �V      �)     �&      Q     �0      *�     �;      P�     �]      ;     �     H            �&     ^	      z0     �
      ~;     �      �G     �      �^     7      Rd     |$      (�     �      M�     �      a�           ȡ     2	      T�     a
      �     �      3�     �      ��     _      @�     9      ��     �      �     �	      %�     s      �
     �      �%     �       �F     �&      �m     �4      "�     Iw      �