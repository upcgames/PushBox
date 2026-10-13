import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import audio_resources

SOURCE = 'void MusicaCongratulations(){ PlaySound(TEXT("Victory.wav"), NULL, SND_ASYNC); }'


class AudioResourcesTest(unittest.TestCase):
    def test_manifest_uses_exact_source_names(self):
        files, ending = audio_resources.audio_manifest(SOURCE, ['Victory.mp3', 'Coin.mp3'])
        self.assertEqual(files, ['Coin.mp3', 'Victory.mp3'])
        self.assertEqual(ending, 'Victory.mp3')

    def test_case_drift_is_rejected_even_on_case_insensitive_hosts(self):
        with self.assertRaisesRegex(ValueError, 'asset spelling: victory.mp3'):
            audio_resources.audio_manifest(SOURCE, ['victory.mp3'])

    def test_missing_asset_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'missing: Victory.mp3'):
            audio_resources.audio_manifest(SOURCE, [])

    def test_ambiguous_casing_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'Ambiguous'):
            audio_resources.audio_manifest(SOURCE, ['Victory.mp3', 'victory.mp3'])

    def test_conflicting_canonical_spellings_are_rejected(self):
        source = SOURCE + 'void Other(){ PlaySound(TEXT("victory.wav"), NULL, 0); }'
        with self.assertRaisesRegex(ValueError, 'missing: victory.mp3'):
            audio_resources.audio_manifest(source, ['Victory.mp3'])

    def test_generation_reads_mp3_assets_without_copying_or_modifying_them(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, target, manifest = root / 'source', root / 'public', root / 'generated' / 'audioAssets.js'
            source.mkdir(); target.mkdir()
            (source / 'Source Code.cpp').write_text(SOURCE)
            (source / 'Victory.wav').write_bytes(b'canonical audio')
            (target / 'Victory.mp3').write_bytes(b'web audio')
            with patch.multiple(audio_resources, SOURCE_DIR=source, TARGET_DIR=target, MANIFEST=manifest):
                audio_resources.generate_audio_manifest()
            self.assertEqual([path.name for path in target.iterdir()], ['Victory.mp3'])
            self.assertEqual((target / 'Victory.mp3').read_bytes(), b'web audio')
            self.assertEqual((source / 'Victory.wav').read_bytes(), b'canonical audio')
            self.assertIn('CONGRATULATIONS_MUSIC = "Victory.mp3"', manifest.read_text())

    def test_web_source_uses_direct_mp3_requests_only_for_sound_calls(self):
        source = SOURCE + 'const char* label = "Victory.wav";'
        result = audio_resources.web_audio_source(source)
        self.assertIn('PlaySound(TEXT("Victory.mp3")', result)
        self.assertIn('label = "Victory.wav"', result)
        self.assertIn('PlaySound(TEXT("Victory.wav")', source)


if __name__ == '__main__':
    unittest.main()
